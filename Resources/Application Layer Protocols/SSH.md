# Secure Shell (SSH)

---

## Background
As a Network Administrator or Software Engineer, remotely working from home may be an option for you. However, in order to do your job away from the office, you still need access to company resources such as applications on company devices or remotely managing a system. To give you a concrete example, let us say that a Network Admin worker was assigned a task of reconfiguring some policies on a router for the company. This router also serves as the company firewall which allows services for blocking incoming traffic. The Network Admin has generally two choice. 1. Drive to work and console cable into the router to make changes to the device through the LAN. 2. Sit in his/her home office chair and SSH into the router. Any sane person would pick option 2 (Which is usually not the case for anyone choosing to do IT). The point is, SSH allows simple management of remote devices from your local device.

---

## What
SSH is a secure, encrypted protocol that establishes a tunnel between two devices, allowing a user to securely manage and interact with a remote system as if they were directly connected. This protocol provides a method for accessing command-line interfaces, file transfers, and remote applications securely over potentially insecure networks like the internet.

---

## Why
SSH is efficient for those who want to directly manage devices from one single point. If SSH was an unencrypted protocol, adversaries peeping in on the connection over the internet would be able to see everything and disrupt/alter communication between devices. SSH keeps security in mind when two hosts want to connect over an unsecure internet.

---

## How
![SSH Protocol](https://substackcdn.com/image/fetch/f_auto,q_auto:good,fl_progressive:steep/https%3A%2F%2Fsubstack-post-media.s3.amazonaws.com%2Fpublic%2Fimages%2Fed998b2e-fbc8-4c3c-b339-eca5abd85ce3_1289x1536.gif)
GIF Source: https://blog.bytebytego.com/p/ep124-how-does-ssh-work

</br>

The control flow of the Secure Shell (SSH) is as follows:

- **DNS Resolution:** Device A performs a DNS lookup to find Device B’s IP address if only the hostname is known.

- **TCP Connection Establishment:** Device A initiates a TCP connection to Device B on port 22, completing a three-way handshake.

- **SSH Protocol Version Exchange:** Device A and Device B exchange supported SSH protocol versions and initial parameters.

- **Key Exchange and Encryption Setup:** Device A and Device B perform a key exchange to establish a shared secret and negotiate encryption settings.

- **Server Authentication:** Device A verifies Device B's identity by checking its public key against the known hosts list.

- **Client Authentication:** Device A authenticates itself to Device B using either password authentication or public key authentication.

- **Session Establishment:** An SSH session is established, allowing secure command execution, file transfer, or port forwarding.

- **Data Transfer and Communication:** Device A and Device B securely exchange encrypted data over the SSH session.

- **Session Termination:** Either Device A or Device B initiates a termination signal to end the session and close the connection.

- **SSH Cache Maintenance:** Device A may store Device B's public key in the known_hosts file for future connections.


---
