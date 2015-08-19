RS .6 Example Plugin
==================

This is somewhat based on the VOIP plugin.

Simplified to make it easier to see how things work.

Features broadcast chat and broadcast paint  
all networking is doing by encoding to json rather than the more compact+speedy but verbose multiple RsItem method.
A good middle ground could be msgpack

To use as a basis for your own plugins you can run

    ./rename_plugin.sh NewPluginName

This will replace all instances of "NetExample" with "NewPluginName"  
you must also change the plugins ID from b00b5 to a number of your choosing.