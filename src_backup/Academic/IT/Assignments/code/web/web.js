const express = require('express');
const puppeteer = require('puppeteer');
const fs = require('fs');
const path = require('path'); // For handling file paths

const app = express();
const PORT = 5500;

// Serve static files from the "public" directory
app.use(express.static('public'));

async function Scrapper() {
    const publicDir = path.join(__dirname, 'public');
    const filePath = path.join(publicDir, 'alumni.json');

    // Ensure "public" directory exists, or create it
    if (!fs.existsSync(publicDir)) {
        fs.mkdirSync(publicDir);
    }

    // Initialize "alumni.json" with an empty array if it doesn't exist
    if (!fs.existsSync(filePath) || fs.readFileSync(filePath).toString().trim() === '') {
        fs.writeFileSync(filePath, JSON.stringify([], null, 2));
    }

    const browser = await puppeteer.launch({ headless: false });
    const page = await browser.newPage();
    const AlumniData = [];

    try {
        await page.goto('https://alumni.uohyd.ac.in/members');
        console.log(`Website Reached`);

        // Login process
        await page.waitForSelector("#email");
        await page.type("#email", "vinith.valbhapur@gmail.com", { delay: 100 });
        await new Promise(r => setTimeout(r, 1000));
        await page.click("#emailBtn");
        await new Promise(r => setTimeout(r, 3000));
        await page.waitForSelector("#passwordLogin");
        await page.type("#passwordLogin", "Vinith@1234");
        await page.waitForSelector(
            '#inside-ui-view > ui-view > main > div.mdl-grid.login-size.contact-div-change.main-family > div > div > div.mdl-cell.mdl-cell--12-col-tablet.login-top-div.login-signup-padding.flexbox.mdl-cell--7-col.login-border > div > form > div:nth-child(4) > button.mdl-button.font-14.ladda-button.ladda-button-primary.mdl-js-button.mdl-button--raised.mdl-button--colored.mdl-typography--font-regular'
        );
        await page.click(
            '#inside-ui-view > ui-view > main > div.mdl-grid.login-size.contact-div-change.main-family > div > div > div.mdl-cell.mdl-cell--12-col-tablet.login-top-div.login-signup-padding.flexbox.mdl-cell--7-col.login-border > div > form > div:nth-child(4) > button.mdl-button.font-14.ladda-button.ladda-button-primary.mdl-js-button.mdl-button--raised.mdl-button--colored.mdl-typography--font-regular'
        );
        await page.waitForNavigation();
        console.log('Successfully logged in');

        // Scraping process
        const selector = '[ng-click*="select_in_level"]';
        await page.waitForSelector(selector);
        const totalCards = (await page.$$(selector)).length;

        for (let i = 0; i < Math.min(totalCards, 10); i++) {
            await page.waitForSelector(selector);
            const cards = await page.$$(selector); // Fresh fetch
            const card = cards[i];

            const title = await card.$eval('span', el => el.textContent.trim());
            console.log(`Clicking on: ${title}`);

            await card.click();
            const selector1 = '[ng-click*="count_obj2.key"]';
            await page.waitForSelector(selector1);
            const totalChildCards = (await page.$$(selector1)).length;

            for (let j = 0; j < totalChildCards; j++) {
                await page.waitForSelector(selector1);
                const ChildCards = await page.$$(selector1); // Fresh fetch
                const Ccard = ChildCards[j];

                const titleChild = await Ccard.$eval('span', el => el.textContent.trim());
                console.log(`Clicking on: ${titleChild}`);

                await Ccard.click();
                await page.waitForSelector('.maximize-width.border-box.padding-12');
                const memberCards = await page.$$('.maximize-width.border-box.padding-12');

                for (const card of memberCards) {
                    const name = await card.$eval('a.link-detail', el => el.textContent.trim());
                    let location = "Unknown";

                    try {
                        location = await card.$eval('div.overflow-ellipsis', el => el.textContent.trim());
                    } catch (err) {
                        // Handle missing location gracefully
                    }

                    const alumni = {
                        name: name,
                        location: location,
                        class: title
                    };

                    AlumniData.push(alumni);

                    // Save data dynamically to the JSON file
                    const existingData = JSON.parse(fs.readFileSync(filePath).toString() || '[]');
                    existingData.push(alumni);
                    fs.writeFileSync(filePath, JSON.stringify(existingData, null, 2));

                    console.log(`Saved: ${name}, ${location}, ${title}`);
                }
                await page.goBack();
                await new Promise(r => setTimeout(r, 2000));
            }
            await page.goBack();
            await new Promise(r => setTimeout(r, 2000));
        }
        console.log('Scraping completed.');
    } catch (error) {
        console.error('Error during scraping:', error);
    } finally {
        await browser.close();
    }
}

// Start the server
app.listen(PORT, () => {
    console.log(`Server Started on port ${PORT}`);
});

// Execute the scraper directly when the server starts
Scrapper();