{
    "targets":[
        {
            "target_name": "addon",
            'include_dirs': [
              '../inc',
              '/usr/include/boost/',
              
            ],
            "sources": [    "init.cc",
                            "Wrapper.cc",
                            "../src/Generator.cpp",
                            "../src/Operations.cpp",
                            "../src/MathNode.cpp",
                            "../src/NodeBuilder.cpp"
                       ],
            'libraries': [
              '-L/usr/lib/x86_64-linux-gnu',
              '-lboost_regex'
            ],
            "cflags": [
              "-std=c++11"
            ]
        }
    ]
}
