const express = require('express');
const puppeteer = require('puppeteer');
const fs = require('fs');

const app = express();
const PORT = 3000;

// CREDENTIALS - TODO: Fill these in or use Environment Variables
const EMAIL = "";     // Enter your email here
const PASSWORD = "";  // Enter your password here

async function Scrapper() {
    if (!EMAIL || !PASSWORD) {
        console.error("Error: Credentials are empty. Please update index.js with your email and password.");
        return;
    }

    console.log("Starting Scraper...");
    const browser = await puppeteer.launch({ headless: false });
    const page = await browser.newPage();

    try {
        await page.goto('https://alumni.uohyd.ac.in/members');
        console.log(`Website Reached`);

        // Login Flow
        await page.waitForSelector("#email");
        await page.type(`#email`, EMAIL, { delay: 100 });
        await new Promise(r => setTimeout(r, 1000));

        await page.click(`#emailBtn`);
        await new Promise(r => setTimeout(r, 3000));

        await page.waitForSelector(`#passwordLogin`);
        await page.type(`#passwordLogin`, PASSWORD);

        // Login Button Click - Selector simplified for readability, ensure it matches live site
        const loginBtnSelector = 'button[type="submit"]'; // Replacing long CSS selector with semantic one if possible, otherwise revert
        // Using the original specific selector to be safe as the site might be tricky
        const originalLoginSelector = '#inside-ui-view > ui-view > main > div.mdl-grid.login-size.contact-div-change.main-family > div > div > div.mdl-cell.mdl-cell--12-col-tablet.login-top-div.login-signup-padding.flexbox.mdl-cell--7-col.login-border > div > form > div:nth-child(4) > button';

        await page.waitForSelector(originalLoginSelector);
        await page.click(originalLoginSelector);
        await page.waitForNavigation();
        console.log('Successfully logged in');

        // Scraping Logic
        const selector = '[ng-click*="select_in_level"]';
        await page.waitForSelector(selector);
        const totalCards = (await page.$$(selector)).length;

        // Initialize Output File
        fs.writeFileSync('./alumni.json', '[\n');
        let isFirst = true;

        for (let i = 0; i < totalCards; i++) {
            await page.waitForSelector(selector);
            const cards = await page.$$(selector);
            const card = cards[i];

            const title = await card.$eval('span', el => el.textContent.trim());
            console.log(`Processing Category: ${title}`);
            await card.click();

            const selector1 = '[ng-click*="count_obj2.key"]';
            await page.waitForSelector(selector1);
            const totalChildCards = (await page.$$(selector1)).length;

            for (let j = 0; j < totalChildCards; j++) {
                await page.waitForSelector(selector1);
                const ChildCards = await page.$$(selector1);
                const Ccard = ChildCards[j];

                await Ccard.click();

                await page.waitForSelector('.maximize-width.border-box.padding-12');
                const memberCards = await page.$$('.maximize-width.border-box.padding-12');

                for (const member of memberCards) {
                    const name = await member.$eval('a.link-detail', el => el.textContent.trim());
                    let location = "Unknown";
                    try {
                        location = await member.$eval('div.overflow-ellipsis', el => el.textContent.trim());
                    } catch {
                        // Location missing
                    }

                    const record = { name, location, class: title };
                    const jsonLine = JSON.stringify(record, null, 2);

                    fs.appendFileSync('./alumni.json', (isFirst ? '' : ',\n') + jsonLine);
                    isFirst = false;

                    console.log(`Saved: ${name}`);
                }

                await page.goBack(); // Back from sub-category
            }

            await page.goBack(); // Back from main category
        }

        // Close JSON array
        fs.appendFileSync('./alumni.json', '\n]');
        console.log("Scraping Complete. Data saved to alumni.json");

    } catch (error) {
        console.error("Scraping failed:", error);
    } finally {
        await browser.close();
    }
}

app.listen(PORT, () => {
    console.log(`Server Started on port ${PORT}`);
    // Optional: Auto-start scraper on server start
    // Scrapper(); 
});

// To run scraper manually:
Scrapper();
