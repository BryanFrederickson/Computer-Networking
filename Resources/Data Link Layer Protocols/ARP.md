# Address Resolution Protocol (ARP)

---

## Background
Imagine you, as a user, want to communicate with another device on the same local network. Your device has an IPv4 address of `192.168.1.1`, and the device you want to contact has an IPv4 address of `192.168.1.2`. For communication to happen, your device needs to send data to `192.168.1.2`. However, IP addresses alone are not sufficient at the data link layer, where actual communication between devices takes place. 

At the data link layer, an IP address is not as valuable as a MAC address, which is a 48-bit hexadecimal representation assigned by the device manufacturer, such as `00:0A:45:2E:52:28`. 

This is where **Address Resolution Protocol (ARP)** comes in—your device uses ARP to map the IP address `192.168.1.2` to the corresponding MAC address of the target device. Once your device knows the MAC address, it can send data to `192.168.1.2` on the local network.

---

## What
The Address Resolution Protocol is essential for LAN communication. Its function is to locate recipient MAC addresses given their corresponding IPv4 addresses, allowing communication between two devices at the data link layer. ARP operates by broadcasting a request to the local network to find the MAC address associated with a specific IP address. The device that owns that IP address responds with its MAC address.

---

## Why
ARP is necessary because, without it, devices on a Local Area Network (LAN) would be unable to locate each other. Since devices communicate at the data link layer using MAC addresses, ARP plays a crucial role in translating IP addresses, which are used at the network layer, into MAC addresses. This translation is vital for enabling successful data transmission between devices within the same network.

---

## How
![Traditional ARP Process](https://www.practicalnetworking.net/wp-content/uploads/2017/01/traditional-arp-process.gif)
GIF Source: https://www.practicalnetworking.net/wp-content/uploads/2017/01/traditional-arp-process.gif

</br>

The control flow of the Address Resolution Protocol (ARP) is as follows:

- **ARP Request Generation**: Device A creates an ARP request to find the MAC address corresponding to Device B's IP address.

- **Broadcasting ARP Request**: Device A broadcasts the ARP request packet to all devices on the local network.

- **Receiving ARP Request**: All devices on the network receive the ARP request and check if the target IP matches their own IP address.

- **ARP Reply Generation**: Device B, recognizing its IP address in the ARP request, prepares an ARP reply with its MAC address.

- **Sending ARP Reply**: Device B sends the ARP reply directly to Device A's MAC address.

- **Receiving ARP Reply**: Device A receives the ARP reply and extracts Device B's MAC address from the packet.

- **Communication**: Device A can now send data frames to Device B using its MAC address.

- **ARP Cache Maintenance**: Device A stores the IP-to-MAC mapping in its ARP cache for future communication.




---
