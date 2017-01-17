'use strict';
console.log(process.version);
const dhsdk = require('./libs/dhsdk/build/Release/dhsdk.node');

//console.log(addon.hello());
// dhsdk.hello(function(msg){
//     console.log(msg);
// });

var a = new dhsdk.CSdkObject();

a.setLogCallback(function(msg){
    console.log(`c++ log : ${msg}`);
});

console.log(`init age = ${a.getAge()}`);

a.setAge(125);
console.log(`after set age = ${a.getAge()}`);

var ret = a.login("192.168.2.89", 37777, "admin", "admin");
console.log(`login dev return ${ret}`);
if(ret != 0){
    var c = a.realStream(0, function(data1, data2){

    });
    console.log(`realstream handle = ${c}`);
}

 console.log("after realstream");
// var a = dhsdk.newPlayer();
//  console.log(a);
               
//  var b = dhsdk.deletePlayer();
//  console.log(b);

const {app} = require('electron');
const {ipcMain} = require('electron');
const {BrowserWindow} = require('electron');
//const dhvideo = require('./libs/dhvideo/addon.node');

let mainWindow = null;




ipcMain.on('win-max', function(e, arg){
    console.log(arg);
    
    if(mainWindow.isMaximized()){
        mainWindow.unmaximize();
         //  mainWindow.webContents.closeDevTools();         
    } else {
        mainWindow.maximize();
        // mainWindow.webContents.openDevTools();
    }
    //e.sender.send('on-win-max', 'win max received.');
});

ipcMain.on('win-mix', function(e, arg){
    console.log(arg);
    
    mainWindow.minimize();
   // e.sender.send('on-win-max', 'win max received.');
});

ipcMain.on('open-page', function(e, arg){


    if(arg === 'video'){
          mainWindow.loadURL(`file://${__dirname}/app/video.html`);
    } else if(arg === 'setting'){

    } else if(arg === 'home'){

    } 


});

ipcMain.on('video-play', function(e, arg){

   // console.log(dhvideo.hello());

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
    
    //mainWindow.loadURL(`file://${__dirname}/app/home.html`);

    mainWindow.loadURL(`file://${__dirname}/app/home.html`);
    mainWindow.webContents.openDevTools();

});

app.on('window-all-closed', function () {
    app.exit();
});