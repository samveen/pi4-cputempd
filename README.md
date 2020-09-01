## Temperature Logger Daemon For My Raspberry Pi 4

I wanted to test how the cheap heatsinks I got for my Raspberry Pi 4 performed
especially when in the official case against the official case without the
cover. For that I wanted to first log the CPU temperature somewhere. While
writing the bash script to log it, I thought why not use some pre-built tool,
which are in abundance. However, a quick 5 minute search showed me that all
the available tools were probably overkill. However, seeing that most tools
were daemons, I decided to write up a quick daemon that would run as a systemd
unit (a simple one) and log the temperature to the journal. This is the result.

# Building And Running

- Install `gcc`
- Run `make`
- Install the binary to `/usr/local/bin`
- Install the service unit into `/etc/systemd/system`
- Enable the unit with `systemctl enable`
- Start up the service with `systemctl start`

# Checking The Output

The service logs for the unit contain the teperature data. It can be seen with
- `journalctl -u pi-cputempd`


# Test Environment

This is running on Ubuntu Focal Fossa 20.04.1 installed on my Raspberry Pi 4B
with 2GB memory (H/W rev 1.2).

# License
This code is released under the `HIRE ME/PAY ME` License (a modified 2 Clause BSD
License). Please see the LICENSE file for details.

# ToDo

- Enable parameter passing (sleep delay, location of the temperature file in sysfs).
- Create a deb control file to create a package.
- Test in  distributions of the RedHat lineage and spec file for packages for
  them.
