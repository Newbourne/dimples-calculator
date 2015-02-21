{
    "targets":[
        {
            "target_name": "addon",
            "sources": [    "init.cc",
                            "Wrapper.cc",
                            "Generator.cpp",
                            "Operations.cpp",
                            "MathNode.cpp",
                            "NodeBuilder.cpp"
                       ],
            'libraries': [
              '-L/usr/local/lib', '-lboost_regex'
            ],
            "conditions": [
                          [ 'OS=="mac"', {
                            "xcode_settings": {
                                'OTHER_CPLUSPLUSFLAGS' : ['-std=c++11','-stdlib=libc++'],
                                'OTHER_LDFLAGS': ['-stdlib=libc++'],
                                'MACOSX_DEPLOYMENT_TARGET': '10.9'
                            }
                        }]
                    ]
        }
    ]
}
