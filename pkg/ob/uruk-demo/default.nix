{ obelisk ? import ./.obelisk/impl {
    system = builtins.currentSystem;
    iosSdkVersion = "10.2";
    # You must accept the Android Software Development Kit License Agreement at
    # https://developer.android.com/studio/terms in order to build Android apps.
    # Uncomment and set this to `true` to indicate your acceptance:
    config.android_sdk.accept_license = true;
  }
}:
with obelisk;
project ./. ({ ... }: {
  packages = {
    urbit-atom = ../../hs/urbit-atom;
    urbit-noun = ../../hs/urbit-noun;
    urbit-noun-core = ../../hs/urbit-noun-core;
    urbit-uruk = ../../hs/urbit-uruk;
    urbit-uruk-rts = ../../hs/urbit-uruk-rts;
  };
  android.applicationId = "systems.obsidian.obelisk.examples.minimal";
  android.displayName = "Obelisk Minimal Example";
  ios.bundleIdentifier = "systems.obsidian.obelisk.examples.minimal";
  ios.bundleName = "Obelisk Minimal Example";
})
