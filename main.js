'use strict';

const {app} = require('electron');
const {ipcMain} = require('electron');
const {BrowserWindow} = require('electron');

let mainWindow = null;


ipcMain.on('win-max', function(e, arg){
    console.log(arg);
    
    if(mainWindow.isMaximized()){
        mainWindow.unmaximize();
           mainWindow.webContents.closeDevTools();         
    } else {
        mainWindow.maximize();
         mainWindow.webContents.openDevTools();
    }
    //e.sender.send('on-win-max', 'win max received.');
});

ipcMain.on('win-mix', function(e, arg){
    console.log(arg);
    
    mainWindow.minimize();
   // e.sender.send('on-win-max', 'win max received.');
});

ipcMain.on('win-close', function(e, arg){
    console.log(arg);
    app.exit();
   // e.sender.send('on-win-max', 'win max received.');
});


app.on('ready', function () {
    mainWindow = new BrowserWindow({
        minWidth: 800,
        minHeight: 600,
        frame:false,
        useContentSize : true

    });
    
    mainWindow.loadURL(`file://${__dirname}/app/home.html`);
   // mainWindow.webContents.openDevTools();

});

app.on('window-all-closed', function () {
    app.exit();
});

