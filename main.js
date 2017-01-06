'use strict';

const {app, BrowserWindow} = require('electron');
let mainWindow = null;



app.on('ready', function () {
    mainWindow = new BrowserWindow({
        minWidth: 800,
        minHeight: 600,
        frame:false,
        useContentSize : true

    });
    
    mainWindow.loadURL(`file://${__dirname}/app/home.html`);
    mainWindow.webContents.openDevTools();

});

app.on('window-all-closed', function () {
    app.exit();
});