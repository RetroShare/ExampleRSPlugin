RS .6 Example Plugin
==================

This is somewhat based on the VOIP plugin.

Simplified to make it easier to see how things work.

Features broadcast chat and broadcast paint  
all networking is doing by encoding to json rather than the more compact+speedy but verbose multiple RsItem method.
A good middle ground could be msgpack

##Compile & run

Depends on qt5.4+

this plugin should be built in the retroshare plugins directory, along the lines of:

    cd myretrosharedir/plugins
    git clone https://github.com/RetroShare/ExampleRSPlugin.git
    cd ExampleRSPlugin
    qmake
    make
    cp *so* ~/.retroshare/extensions6/

Then reboot retroshare, it will ask if you want to accept the plugin.

##Build Plugin based on this plugin

To use as a basis for your own plugins you can run

    ./rename_plugin.sh NewPluginName

This will replace all instances of "NetExample" with "NewPluginName"
you must also change the plugins ID from 12345 to a number of your choosing.
