cmd_/home/user/EmbeddedLinux/driver-model/v1/modules.order := {   echo /home/user/EmbeddedLinux/driver-model/v1/dummy_serial.ko; :; } | awk '!x[$$0]++' - > /home/user/EmbeddedLinux/driver-model/v1/modules.order