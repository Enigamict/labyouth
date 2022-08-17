# !/bin/bash
set -eux

# Network Namespaceの作成
ip netns add C1
ip netns add C2
ip netns add R1
ip netns add R2
ip netns add R3
ip netns add R4
ip netns add R5
ip netns add C3
ip netns add C4

# インターフェースの作成

ip link add name C1_net0 type veth peer name R1_net2
ip link add name C2_net0 type veth peer name R1_net3

ip link add name R1_net0 type veth peer name R3_net0
ip link add name R1_net1 type veth peer name R4_net0

ip link add name R3_net1 type veth peer name R2_net0
ip link add name R4_net1 type veth peer name R5_net0

ip link add name R5_net1 type veth peer name R2_net1

ip link add name C3_net0 type veth peer name R2_net2
ip link add name C4_net0 type veth peer name R2_net3

# インターフェースを各Namespaceに所属させる
ip link set C1_net0 netns C1
ip link set C2_net0 netns C2

ip link set R1_net0 netns R1
ip link set R1_net1 netns R1
ip link set R1_net2 netns R1
ip link set R1_net3 netns R1

ip link set R2_net0 netns R2
ip link set R2_net1 netns R2
ip link set R2_net2 netns R2
ip link set R2_net3 netns R2

ip link set R3_net0 netns R3
ip link set R3_net1 netns R3

ip link set R4_net0 netns R4
ip link set R4_net1 netns R4

ip link set R5_net0 netns R5
ip link set R5_net1 netns R5

ip link set C3_net0 netns C3
ip link set C4_net0 netns C4

# インターフェースへIPアドレスを付与
ip netns exec C1 ip addr add 10.1.0.2/24 dev C1_net0
ip netns exec C2 ip addr add 10.2.0.2/24 dev C2_net0

ip netns exec R1 ip addr add 10.255.1.1/24 dev R1_net0
ip netns exec R1 ip addr add 10.255.3.1/24 dev R1_net1
ip netns exec R1 ip addr add 10.1.0.1/24 dev R1_net2
ip netns exec R1 ip addr add 10.2.0.1/24 dev R1_net3

ip netns exec R2 ip addr add 10.255.2.2/24 dev R2_net0
ip netns exec R2 ip addr add 10.255.5.2/24 dev R2_net1
ip netns exec R2 ip addr add 10.3.0.1/24 dev R2_net2
ip netns exec R2 ip addr add 10.4.0.1/24 dev R2_net3

ip netns exec R3 ip addr add 10.255.1.3/24 dev R3_net0
ip netns exec R3 ip addr add 10.255.2.3/24 dev R3_net1

ip netns exec R4 ip addr add 10.255.3.4/24 dev R4_net0
ip netns exec R4 ip addr add 10.255.5.4/24 dev R4_net1

ip netns exec R5 ip addr add 10.255.4.5/24 dev R5_net0
ip netns exec R5 ip addr add 10.255.5.5/24 dev R5_net1

ip netns exec C3 ip addr add 10.3.0.2/24 dev C3_net0
ip netns exec C4 ip addr add 10.4.0.2/24 dev C4_net0


ip netns exec C1 ip link set C1_net0 up
ip netns exec C2 ip link set C2_net0 up

ip netns exec R1 ip link set R1_net0 up
ip netns exec R1 ip link set R1_net1 up
ip netns exec R1 ip link set R1_net2 up
ip netns exec R1 ip link set R1_net3 up

ip netns exec R2 ip link set R2_net0 up
ip netns exec R2 ip link set R2_net1 up
ip netns exec R2 ip link set R2_net2 up
ip netns exec R2 ip link set R2_net3 up

ip netns exec R3 ip link set R3_net0 up
ip netns exec R3 ip link set R3_net1 up

ip netns exec R4 ip link set R4_net0 up
ip netns exec R4 ip link set R4_net1 up

ip netns exec R5 ip link set R5_net0 up
ip netns exec R5 ip link set R5_net1 up

ip netns exec C3 ip link set C3_net0 up
ip netns exec C4 ip link set C4_net0 up

ip -all netns exec ip link set lo up

ip netns exec C1 ip route add 0.0.0.0/0 via 10.1.0.1
ip netns exec C2 ip route add 0.0.0.0/0 via 10.2.0.1

ip netns exec R1 ip route add 10.3.0.0/24 via 10.255.1.3
ip netns exec R1 ip route add 10.4.0.0/24 via 10.255.1.3

ip netns exec C3 ip route add 0.0.0.0/0 via 10.3.0.1
ip netns exec C4 ip route add 0.0.0.0/0 via 10.4.0.1

ip netns exec R2 ip route add 10.1.0.0/24 via 10.255.2.3
ip netns exec R2 ip route add 10.2.0.0/24 via 10.255.2.3

ip netns exec R3 ip route add 10.3.0.0/24 via 10.255.2.2
ip netns exec R3 ip route add 10.4.0.0/24 via 10.255.2.2
ip netns exec R3 ip route add 10.1.0.0/24 via 10.255.1.1
ip netns exec R3 ip route add 10.2.0.0/24 via 10.255.1.1

ip netns exec R4 ip route add 10.1.0.0/24 via 10.255.3.1
ip netns exec R4 ip route add 10.2.0.0/24 via 10.255.3.1
ip netns exec R4 ip route add 10.3.0.0/24 via 10.255.5.5
ip netns exec R4 ip route add 10.4.0.0/24 via 10.255.5.5

ip netns exec R5 ip route add 10.1.0.0/24 via 10.255.4.4
ip netns exec R5 ip route add 10.2.0.0/24 via 10.255.4.4
ip netns exec R5 ip route add 10.3.0.0/24 via 10.255.5.2
ip netns exec R5 ip route add 10.4.0.0/24 via 10.255.5.2

ip netns exec R1 sysctl -w net.ipv4.ip_forward=1
ip netns exec R2 sysctl -w net.ipv4.ip_forward=1
ip netns exec R3 sysctl -w net.ipv4.ip_forward=1
ip netns exec R4 sysctl -w net.ipv4.ip_forward=1
