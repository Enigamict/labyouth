package main

/*
#cgo LDFLAGS: -L. -lipv4add
#include "libnetlink.h"
#include "ipv4add.h"
*/
import "C"

func main() {
	//fd := C.rtnl_open()
	//C.rtnl_listen(fd)
	C.ipv4_route_add(C.CString("5.4.3.4"), C.CString("10.2.0.1"))
}
