const puppeteer = require('puppeteer');
const path = require('path');
const fs = require('fs');

if (process.argv.length !== 5) {
  console.error('Usage: node script.js <url> <timeout> <screenshotFolderPath>');
  process.exit(1);
}

const url = process.argv[2];
const timeout = parseInt(process.argv[3]);
const screenshotFolderPath = process.argv[4];
const domain = new URL(url).hostname;
const screenshotPath = path.join(screenshotFolderPath, `${domain}.png`);

(async () => {
  const browser = await puppeteer.launch({
    headless: 'new',
    args: ['--no-sandbox']
  });

  const page = await browser.newPage();

  try {
    await page.goto(url, { timeout });
    await page.screenshot({ path: screenshotPath });
  } catch (error) {
  } finally {
    await browser.close();
  }

  process.exit(0);
})();

