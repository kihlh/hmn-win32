{
  "targets": [
    {
      "target_name": "HMN_x64",
      # "target_name": "HMN_x86",
      "conditions": [
        ['OS=="win"', {
          "sources": [
            "sock_lib/ip.cpp",
            "sock_lib/connect_net.cpp",
            "sock_lib/ping.cpp",
            "Main.cpp"
          ],
          'msvs_settings': {
            'VCCLCompilerTool': {
              'AdditionalOptions': [
                '/W3',
                '/Qspectre',
                '/guard:cf',
                "/wd4819",
                "/wd4067",
                "/wd4101",
                "/wd4312",
                "/wd4311",
                "/wd4302",
                "/wd4060",
                "/wd4700",
                "/wd4081",
                "/wd4530",
                "/wd4715",
                "/wd4018"
              ]
            },
            'VCLinkerTool': {
              'AdditionalOptions': [
                '/guard:cf'
              ]
            }
          },
        }]
      ]
    }
  ]
}
