idf_component_register(SRCS "plant.c" "ADCmanager.c" "wifimanager.c" "httpmanager.c" "ledmanager.c" "mqttmanager.c" "parser.c"
                    INCLUDE_DIRS "." 
                    EMBED_TXTFILES root_cert.pem)
