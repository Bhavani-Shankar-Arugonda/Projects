const express = require('express');
const puppeteer = require('puppeteer');
const fs = require('fs');

const ScrapWebsite = async () => {
    const browser = await puppeteer.launch();
    const page = await browser.newPage();
    await page.goto('https://alumni.uohyd.ac.in/members');
    const pageTitle = await page.title();
    console.log(pageTitle+'reached');

    await page.waitForSelector("#email");
    await page.type(`#email`,`23mcce13@uohyd.ac.in`,{delay:100});
    await new Promise(r => setTimeout(r, 2500));

    await page.click(`#emailBtn`);
    await new Promise(r => setTimeout(r, 2500));
    await page.waitForSelector(`#passwordLogin`);
    await page.type(`#passwordLogin`,`Shankar@8168`);

    await page.waitForSelector('#inside-ui-view > ui-view > main > div.mdl-grid.login-size.contact-div-change.main-family > div > div > div.mdl-cell.mdl-cell--12-col-tablet.login-top-div.login-signup-padding.flexbox.mdl-cell--7-col.login-border > div > form > div:nth-child(4) > button.mdl-button.font-14.ladda-button.ladda-button-primary.mdl-js-button.mdl-button--raised.mdl-button--colored.mdl-typography--font-regular');
    await page.click('#inside-ui-view > ui-view > main > div.mdl-grid.login-size.contact-div-change.main-family > div > div > div.mdl-cell.mdl-cell--12-col-tablet.login-top-div.login-signup-padding.flexbox.mdl-cell--7-col.login-border > div > form > div:nth-child(4) > button.mdl-button.font-14.ladda-button.ladda-button-primary.mdl-js-button.mdl-button--raised.mdl-button--colored.mdl-typography--font-regular');

    

    await browser.close();
}

ScrapWebsite()