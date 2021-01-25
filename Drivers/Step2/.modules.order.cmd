cmd_/home/user/EmbeddedLinux/Drivers/Step2/modules.order := {   echo /home/user/EmbeddedLinux/Drivers/Step2/driver2.ko; :; } | awk '!x[$$0]++' - > /home/user/EmbeddedLinux/Drivers/Step2/modules.order
