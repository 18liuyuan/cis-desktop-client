```
windows下环境安装
```
1、安装nodejs(v6.5.0-x86)
2、npm全局安装electron(v1.4.14-x86)、node-gyp
3、安装python(2.7版本)
4、安装VS2015

```
编译要点
```
node-gyp :
node-gyp rebuild --target=1.4.14 --arch=ia32 --dist-url=https://atom.io/download/electron

```
npm国内淘宝镜像设置
编辑 ~/.npmrc 加入下面内容
registry = https://registry.npm.taobao.org
```