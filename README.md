git clone https://github.com/greigs/kb-node.git
cd kb-node
npm install
npm install serialport --msvs_version=2013
cd node_modules/serialport
node-pre-gyp rebuild --runtime=node-webkit --target=0.12.0  --target_arch=ia32 --msvs_version=2013
mv build/serialport/v1.6.3/Release/node-webkit-v0.12.0-win32-ia32 build/serialport/v1.6.3/Release/node-webkit-v43-win32-ia32
cd ../..
nw 