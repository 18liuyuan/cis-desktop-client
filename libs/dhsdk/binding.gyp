{
    "targets" : [
        {
            "target_name" : "dhsdk",
            "sources" : ["*.cc","*.cpp"],
            "conditions" : [
                [
                    "OS=='win'",{
                        "link_settings":{
                            "libraries":[
                                "-l../lib/dhnetsdk.lib"
                            ]
                        }
                    }
                ]

            ]
        }

    ]

}