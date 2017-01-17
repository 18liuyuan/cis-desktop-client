$(document).ready(function () {
    const{ipcRenderer} = nodeRequire('electron');
   // var main = nodeRequire('remote').nodeRequire('main.js');
    ipcRenderer.on('on-win-max', function(e, arg){
                   
        alert(arg);
    });

    $("#win-max").click(function () {
        ipcRenderer.send('win-max',"aaa");
    });

    $("#win-min").click((e) => {
        ipcRenderer.send('win-mix',"aaa");
    });

    $("#win-close").click((e) => {
         ipcRenderer.send('win-close',"aaa");
    });

    $("#btn-play").click((e) => {
        ipcRenderer.send('video-play',"1");
    });

    var vlc = document.getElementById("vlc");
    vlc.audio.toggleMute();

});