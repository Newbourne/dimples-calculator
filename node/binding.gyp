{
    "targets":[
        {
            "target_name": "addon",
            "include_dirs": [
              "../inc",
              "/usr/include/boost/",
              
            ],
            "sources": [    "init.cc",
                            "Wrapper.cc",
                            "../src/Generator.cpp",
                            "../src/Operations.cpp",
                            "../src/MathNode.cpp",
                            "../src/Situation.cpp"
                       ],
            "libraries": [
              "-L/usr/lib/x86_64-linux-gnu",
              "-lboost_regex"
            ],
            "cflags": [
              "-std=c++0x",
              "-fexceptions",
              "-fno-rtti"
            ],
            "cflags_cc!": [ "-fno-rtti", "-fno-exceptions" ],
            "cflags!": [ "-fno-exceptions" ],
        }
    ]
}
