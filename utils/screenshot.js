/*
 * SCREENSHOT.JS
 * by oldteam & lomaster
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 *   Сделано от души 2023.
 *
 * Утилита на nodejs для создания скриншота WEB страницы.
 * Это единственная реализация без драйверов браузера,
 * которую я нашел.
 *
 * Что бы она стала работать при запуске с sudo, -
 * нужно прописать на папку utils/ такую команду:
 *   sudo chmod u+rwx,g+r,o+r utils/ 
*/

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

(async () =>{
  const browser = await puppeteer.launch
  ({
    headless: 'new',
    args: ['--no-sandbox']
  });

  const page = await browser.newPage();

  try {
    await page.goto(url, { timeout });
    await page.screenshot({ path: screenshotPath });
  }
  catch (error)
  {

  }
  finally
  {
    await browser.close();
  }

  process.exit(0);
})();
