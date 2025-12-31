const express = require('express');
const puppeteer = require('puppeteer');
const fs = require('fs');
const path = require('path');
const { Parser } = require('json2csv');

const app = express();
const PORT = 3000;

app.use(express.static('public'));

async function scrapeAlumniData() {
    const browser = await puppeteer.launch({ headless: true });
    const page = await browser.newPage();
    const alumniRecords = [];

    try {
        await page.goto('https://alumni.uohyd.ac.in/members', { waitUntil: 'domcontentloaded' });

        await page.type('#email', '23mcce13@uohyd.ac.in', { delay: 80 });
        await page.click('#emailBtn');
        await page.waitForTimeout(2000);

        await page.type('#passwordLogin', 'Shankar@8168');
        await page.click('button[type="submit"]');
        await page.waitForNavigation();

        const categorySelector = '[ng-click*="select_in_level"]';
        await page.waitForSelector(categorySelector);
        const categories = await page.$$(categorySelector);

        for (let i = 0; i < Math.min(5, categories.length); i++) {
            await categories[i].click();
            await page.waitForTimeout(1500);

            const subCategorySelector = '[ng-click*="count_obj2.key"]';
            await page.waitForSelector(subCategorySelector);
            const subCategories = await page.$$(subCategorySelector);

            for (let j = 0; j < subCategories.length; j++) {
                await subCategories[j].click();
                await page.waitForTimeout(1500);

                const cardSelector = '.maximize-width.border-box.padding-12';
                const memberCards = await page.$$(cardSelector);

                for (const card of memberCards) {
                    const name = await card.$eval('a.link-detail', el => el.textContent.trim());
                    let location = "Unknown";

                    try {
                        location = await card.$eval('div.overflow-ellipsis', el => el.textContent.trim());
                    } catch {}

                    alumniRecords.push({ name, location });
                }

                await page.goBack();
                await page.waitForTimeout(1000);
            }

            await page.goBack();
            await page.waitForTimeout(1000);
        }

        const csv = new Parser({ fields: ['name', 'location'] }).parse(alumniRecords);
        fs.writeFileSync(path.join(__dirname, 'public', 'alumni.csv'), csv);

    } catch (err) {
        console.error('Scraping error:', err);
    } finally {
        await browser.close();
    }
}

app.get('/start-scraping', async (req, res) => {
    await scrapeAlumniData();
    res.json({ message: 'Scraping completed! Download CSV below.' });
});

app.listen(PORT, () => {
    console.log(`Server running at http://localhost:${PORT}`);
});
