# Routers

---

![Router Image](https://blog.teufel.de/wp-content/uploads/2017/06/what-is-a-router.jpg)
Image Source: https://blog.teufel.de/wp-content/uploads/2017/06/what-is-a-router.jpg

## Scenario
Have you ever wondered how you can access web pages, videos, or any form of media on the internet? Well, you can thank your home router for that. Suppose I'm bored at home and want to watch a video to see how routers work. For my mobile phone to display the video, I need to navigate to YouTube and enter the video name. However, the request I send for the video doesn’t remain within my local area network (LAN)! It must travel through an intermediary to reach a YouTube server located in the wide area network (WAN). Your router serves as the gateway from your LAN to the WAN, allowing you to access internet resources.

You see, the internet isn't just an imaginary cloud depicted in pictures that "holds everything" for you to access. Instead, the internet is a vast network of LANs connected together through electromagnetic signals and cables over long distances.

---

## What
A router connects multiple networks, allowing devices on different networks to communicate by determining the best path for data transmission. Just like the devices you use at home, a router contains a private IP address. But, it also has a public WAN facing IP address! What do I mean when I say "public facing"? Well, This "public" IP address is used by all the devices in a LAN to access infromation in the WAN (Deeper explantion provided in the **How**). Routers have many useful interfaces/features on them which make them so useful! 

For example, some features are:

- **Physical Ports for Ethernet**: Standard RJ-45 ports for wired connections to devices within a local area network (LAN).
- **WAN Ports**: Ports dedicated to connecting the router to a wide area network (WAN) or the internet, often through a modem.
- **Fiber Optic Ports**: Interfaces for connecting to fiber optic networks, offering high-speed internet access.
- **Wireless Interfaces (Wi-Fi)**: Built-in antennas and transceivers to provide wireless connectivity for devices within the network.
- **USB Ports**: USB interfaces for connecting external storage devices, printers, or for 4G/5G LTE modems.
- **Console Port**: A serial port used for initial setup and management of the router, typically accessed via a console cable and terminal software.
- **Management Interfaces**: Web-based or command-line interfaces for configuring and managing the router settings.
- **Power Interface**: Connects the router to a power source, often with an adapter for different voltage requirements.

With the latest versions of routers produced by companies such as Cisco, NETGEAR or Juniper, these devices come in an all-in-one device that performs as a modem which can connect directly to your ISP, a firewall for secuirty in your network, and the basic functionalities as a standard router. This makes your purchasing decisions significantly easier and more effecient to manage! Additionally, many of these devices offer built-in features such as advanced Quality of Service (QoS) for prioritizing bandwidth, support for Virtual Private Networks (VPNs) for secure remote access, and integrated Wi-Fi capabilities to provide wireless connectivity throughout your home or office. Furthermore, they often include user-friendly management interfaces and mobile apps that simplify network setup and monitoring, ensuring that both novice and experienced users can effectively manage their network environments.

---

## Why
Routers are essential for enabling communication between devices across different networks, managing data traffic, and providing connectivity to the internet. They perform several critical functions:

- **Traffic Management:** Routers efficiently direct data packets between networks based on their IP addresses, ensuring that data reaches its intended destination with minimal delay.
- **Network Isolation:** By connecting different networks, routers help maintain network isolation, enhancing security and reducing traffic congestion within a local area network (LAN).
- **Firewall Protection:** Many routers come with built-in firewall features that monitor and control incoming and outgoing network traffic, protecting devices on the network from unauthorized access and potential threats.
- **Address Translation:** Routers use Network Address Translation (NAT) to allow multiple devices on a LAN to share a single public IP address. This not only conserves IP addresses but also adds an extra layer of security by hiding the internal IP addresses of devices.
- **Quality of Service (QoS):** Routers can prioritize traffic for specific applications or devices, ensuring that critical services like video streaming and online gaming receive the bandwidth they need for optimal performance.Routers are essential for enabling communication between devices across different networks, managing data traffic, and providing connectivity to the internet.

---

## How
![Router GIF](https://www.fiber-mart.com/images/newso/router-lan123.gif)  
GIF Source: https://www.fiber-mart.com/images/newso/router-lan123.gif

</br>

Control Flow from End User to End User on Different LANs

- **User Device Initiates Request**: The user device sends a data packet to the router using its private IP address.
- **Router Receives Packet**: The router receives the packet and checks the destination IP address to determine if it’s on the same LAN or needs to be routed externally.
- **Address Resolution Protocol (ARP)**: If the destination IP address is not on the same LAN, the router uses ARP to resolve the destination IP address to a MAC address if it’s in the same network segment.
- **Packet Routing**: If the destination is in a different network, the router forwards the packet to the appropriate gateway based on its routing table.
- **Next Hop Router**: The packet may pass through multiple routers, each determining the best route until it reaches the router that connects to the destination network.
- **Final Router Sends Packet**: The final router in the destination network checks the packet's destination IP address and delivers it to the appropriate user device on that private network.
- **User Device Receives Data**: The destination user device receives the packet, which is reassembled into the original data for the user to access.

---


