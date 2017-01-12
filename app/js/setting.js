$(document).ready(function () {

  const {ipcRenderer} = nodeRequire('electron');

  $("body").prepend("<div id='cis-title-bar-content'></div>");
        $("#cis-title-bar-content").load('cis-title-bar.html', function () {
            $("#win-max").click(function () {
                ipcRenderer.send('win-max', "aaa");
            });

            $("#win-min").click((e) => {
                ipcRenderer.send('win-mix', "aaa");
            });

            $("#win-close").click((e) => {
                ipcRenderer.send('win-close', "aaa");
            });
        });

 
  
    // var main = nodeRequire('remote').nodeRequire('main.js');
    ipcRenderer.on('on-win-max', function (e, arg) {

        alert(arg);
    });



    $("#btn-test").click((e) => {
        alert("test");
    });
});