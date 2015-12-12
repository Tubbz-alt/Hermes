#Hermes -
 
##Install
```
 sudo python3.4 setup.py install
```

###Needed dependencies
 - Python3.4 or highter

##Quickstart
```
 from hermes.Text import Text
 t = Text()
 t.generate_id( "some_uri" )
 t._metadata["description"] = "some_description"
 t.save( "some_directory" )
```
