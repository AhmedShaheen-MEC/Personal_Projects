#!/bin/sh

echo "Check bridge interface status.."

int_status_br=$(sudo cat /sys/class/net/tap0/operstate)
int_status_tap=$(sudo cat /sys/class/net/ppp0/operstate)

if [ "${int_status_br}" != "up" ] && [ "$int_status_tap" != "up" ]; then
        echo "  Installing bridge network interfaces"
		sudo /home/bridge_setup.sh
        echo "Bride setup installed"

fi 


port=1194
echo "Setting up iptable entries"
echo "Used Port:" $port
sudo iptables -t nat -I POSTROUTING 1 -s 192.168.1.0/24 -o br0 -j MASQUERADE
sudo iptables -I INPUT 1 -i tap0 -j ACCEPT
sudo iptables -I FORWARD 1 -i br0 -o tap0 -j ACCEPT
sudo iptables -I FORWARD 1 -i tap0 -o br0 -j ACCEPT
sudo iptables -I INPUT 1 -i br0 -p udp --dport $port -j ACCEPT

sudo iptables -A INPUT -i tap0 -j ACCEPT
sudo iptables -A INPUT -i br0 -j ACCEPT
sudo iptables -A FORWARD -i br0 -j ACCEPT

echo "Done..."