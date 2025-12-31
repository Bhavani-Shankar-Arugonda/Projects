const express = require('express');
const puppeteer = require('puppeteer');
const fs = require('fs');

const app = express();
const PORT = 3000;

async function Scrapper() {
    const browser = await puppeteer.launch({ headless: false });
    const page = await browser.newPage();

    await page.goto('https://alumni.uohyd.ac.in/members');
    console.log(`Website Reached`);

    await page.waitForSelector("#email");
    await page.type(`#email`, `23mcce13@uohyd.ac.in`, { delay: 100 });
    await new Promise(r => setTimeout(r, 1000));
    await page.click(`#emailBtn`);
    await new Promise(r => setTimeout(r, 3000));

    await page.waitForSelector(`#passwordLogin`);
    await page.type(`#passwordLogin`, `Shankar@8168`);
    await page.waitForSelector(`#inside-ui-view > ui-view > main > div.mdl-grid.login-size.contact-div-change.main-family > div > div > div.mdl-cell.mdl-cell--12-col-tablet.login-top-div.login-signup-padding.flexbox.mdl-cell--7-col.login-border > div > form > div:nth-child(4) > button`);
    await page.click(`#inside-ui-view > ui-view > main > div.mdl-grid.login-size.contact-div-change.main-family > div > div > div.mdl-cell.mdl-cell--12-col-tablet.login-top-div.login-signup-padding.flexbox.mdl-cell--7-col.login-border > div > form > div:nth-child(4) > button`);
    await page.waitForNavigation();
    console.log('Successfully logged in');

    const selector = '[ng-click*="select_in_level"]';
    await page.waitForSelector(selector);
    const totalCards = (await page.$$(selector)).length;

    // Start the JSON file
    fs.writeFileSync('./alumni.json', '[\n');
    let isFirst = true;

    for (let i = 0; i < totalCards; i++) {
        await page.waitForSelector(selector);
        const cards = await page.$$(selector);
        const card = cards[i];

        const title = await card.$eval('span', el => el.textContent.trim());
        console.log(`Clicking on: ${title}`);
        await card.click();

        const selector1 = '[ng-click*="count_obj2.key"]';
        await page.waitForSelector(selector1);
        const totalChildCards = (await page.$$(selector1)).length;

        for (let j = 0; j < totalChildCards; j++) {
            await page.waitForSelector(selector1);
            const ChildCards = await page.$$(selector1);
            const Ccard = ChildCards[j];

            const titleChild = await Ccard.$eval('span', el => el.textContent.trim());
            console.log(`Clicking on: ${titleChild}`);
            await Ccard.click();

            await page.waitForSelector('.maximize-width.border-box.padding-12');
            const memberCards = await page.$$('.maximize-width.border-box.padding-12');

            for (const card of memberCards) {
                const name = await card.$eval('a.link-detail', el => el.textContent.trim());
                let location;
                try {
                    location = await card.$eval('div.overflow-ellipsis', el => el.textContent.trim());
                } catch {
                    location = "Unknown";
                }

                const record = { name, location, class: title };

                // Append record as JSON to file
                const jsonLine = JSON.stringify(record, null, 2);
                fs.appendFileSync('./alumni.json', (isFirst ? '' : ',\n') + jsonLine);
                isFirst = false;

                console.log(`Saved: ${name}, ${location}, ${title}`);
            }

            await page.goBack(); // Go back from child
        }

        await page.goBack(); // Go back from main
    }

    // Close JSON array
    fs.appendFileSync('./alumni.json', '\n]');
    await browser.close();
}

app.listen(PORT, () => {
    console.log(`Server Started on port ${PORT}`);
});

Scrapper();
