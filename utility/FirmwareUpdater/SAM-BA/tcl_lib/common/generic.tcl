#  ----------------------------------------------------------------------------
#          ATMEL Microcontroller Software Support
#  ----------------------------------------------------------------------------
#  Copyright (c) 2014, Atmel Corporation
#
#  All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions are met:
#
#  - Redistributions of source code must retain the above copyright notice,
#  this list of conditions and the disclaimer below.
#
#  Atmel's name may not be used to endorse or promote products derived from
#  this software without specific prior written permission. 
#
#  DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
#  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
#  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
#  DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
#  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
#  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
#  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
#  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
#  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
#  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#  ----------------------------------------------------------------------------

################################################################################
################################################################################
## NAMESPACE GENERIC
################################################################################
################################################################################
namespace eval GENERIC {

    # Following variables are updated by the Init function
    variable appletAddr
    variable appletMailboxAddr
    
    # Following variables are set by the Init function
    variable appletBufferAddress
    variable appletBufferSize
    variable memorySize   0
    variable startAddress 0
    variable nandflashInitialized 0
    # Ecc status: 0= ECC_NO, 1= ECC_SOFT, 2=ECC_PMECC, 3=ECC_INTERNAL
    variable nandflashEccStatus   0
    variable nandflashCurParam    0

    # Standard applet commands
    array set appletCmd {
        init            0x00
        erase           0x01
        write           0x02
        read            0x03
        lock            0x04
        unlock          0x05
        gpnvm           0x06
        security        0x07
        erasebuffer     0x08
        binarypage      0x09
        otpRead         0x0a
        otpWrite        0x0b
        listbadblocks   0x10
        tagBlock        0x11
        readUniqueID    0x12
        eraseBlocks     0x13
        batchErase      0x14
        pmeccParam      0x15
        pmeccBoot       0x16
        switchEccMode   0x17
        trimffsMode     0x18
        qspixip         0x19
    }

    #===============================================================================
    # Set trace level for applets
    # 5 : trace_NONE    - No trace will be printed
    # 4 : trace_FATAL   - Indicates a major error which prevents the program from
    #                     going any further.
    # 3 : trace_ERROR   - Indicates an error which may not stop the program
    #                     execution, but which indicates there is a problem with
    #                     the code.
    # 2 : trace_WARNING - Indicates that a minor error has happened. In most case
    #                     it can be discarded safely; it may even be expected.
    # 1 : trace_INFO    - Informational trace about the program execution. Should
    #                     enable the user to see the execution flow.
    # 0 : trace_DEBUG   - Traces whose only purpose is for debugging the program,
    #                     and which do not produce meaningful information otherwise.
    
}

#===============================================================================
#  proc GENERIC::UpdateStatusLabel
#-------------------------------------------------------------------------------
proc GENERIC::UpdateStatusLabel { dataLeft dataInTotal } {
    global softwareStatusLabelVariable
    global commandLineMode

    set softwareStatusLabelVariable ""
    set percent [expr $dataInTotal - $dataLeft]
    set percent [expr $percent.00 / $dataInTotal * 100]
    set percent [expr "int($percent)"]

    if {$commandLineMode == 0} {
        set softwareStatusLabelVariable "Complete $percent%"
    } else {
        puts "-I- Complete $percent%"
    }
}

#===============================================================================
#  proc GENERIC::LoadApplet
#-------------------------------------------------------------------------------
proc GENERIC::LoadApplet {appletAddr appletFileName} {
    global target
    global libPath

    puts "-I- Loading applet [file tail $appletFileName] at address [format "0x%X" $appletAddr]"
    
    # Open Data Flash Write file
    if { [catch {set f [open $appletFileName r]}] } {
        error "Can't open file $appletFileName"
    }

    # Copy applet into Memory at the  appletAddr 
    fconfigure $f -translation binary
    set size [file size $appletFileName]
    set appletBinary [read $f $size]
    if {[catch {TCL_Write_Data $target(handle) $appletAddr appletBinary $size dummy_err} dummy_err]} {
        error "Can't write applet $appletFileName"
    }
    close $f    
}

#===============================================================================
#  proc GENERIC::Run
#
#  Launch the applet, wait for the end of execution and return the result
#-------------------------------------------------------------------------------
proc GENERIC::Run { cmd } {
    global target
    global chip_id
    global samba_os
    global commandLineMode
    variable appletAddr
    variable appletCmd
    variable appletMailboxAddr
    
    set appletCmdAddr    [expr $appletMailboxAddr]
    set appletStatusAddr [expr $appletMailboxAddr + 4]
    
#    puts "-I- Running applet command $cmd at address [format "0x%X" $appletAddr]"

    # Launch the applet Jumping to the appletAddr
    if {[catch {TCL_Go $target(handle) $appletAddr} dummy_err] } {
        error "Error Running the applet"
    }
    # Fix SAM9G45 ROM Code 1.6 : COM port connection require a # character after a go
    #if {($chip_id == 0x819b05a2)} {

     #   if {($target(comType) == 1)} {
     #       if {[catch {TCL_Go $target(handle) $appletAddr} dummy_err] } {
     #           error "Error Running the applet"
     #       }
     #       puts "-I- Second # sent"
     #   }
    #}

    if {[regexp "linux" $samba_os]} {
         set result $cmd
        while {$result != [expr ~($cmd)]} {
            if {[catch {set result [TCL_Read_Int $target(handle) $appletCmdAddr]} dummy_err] } {
                error "Error polling the end of applet execution"
            }
        }
        # Return the error code returned by the applet
        if {[catch {set result [TCL_Read_Int $target(handle) $appletStatusAddr]} dummy_err] } {
            error "Error reading the applet result"
        }
    } else {
        # Wait 10ms for applet running
        after 10
        # Wait for the end of execution
        # Check if applet has finished the job. 
        # Retry 10 times
        if {$cmd == $appletCmd(erase)} {
            set RETRY 25
        } else {
            set RETRY 10
        }
        
        set result $cmd
        for {set timeout 0} {$timeout < $RETRY} {incr timeout 1} {
            if {[catch {set result [TCL_Read_Int $target(handle) $appletCmdAddr]} dummy_err] } {
                error "Error polling the end of applet execution"
            }
            if {$result == [expr ~($cmd)]} {
                break
            }
            # Wait 1s if applet has not finished the job
            after 1000
        }
        # Time out
        if {$timeout >= $RETRY} {
            if {$commandLineMode == 0} {
                set answer [tk_messageBox -title "TIME OUT"\
                -message "The applet did not return.\nPlease check the connection and reconnect the target device." -icon error -type ok]
            }
            error "-E- Timeout: The applet did not return. \nPlease check the connection and reconnect the target device."
        }

        # Return the error code returned by the applet
        if {[catch {set result [TCL_Read_Int $target(handle) $appletStatusAddr]} dummy_err] } {
            error "Error reading the applet result"
        }
    }
    return $result
}

#===============================================================================
#  proc GENERIC::Write
#-------------------------------------------------------------------------------
proc GENERIC::Write {offset sizeToWrite File isBootFile} {
    global target
    variable appletArg
    variable appletCmd
    variable appletAddr
    variable appletMailboxAddr
    variable appletBufferAddress
    variable stepSize
    set dummy_err 0
        
    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArgv0     [expr $appletMailboxAddr + 0x08]
    set appletAddrArgv1     [expr $appletMailboxAddr + 0x0c]
    set appletAddrArgv2     [expr $appletMailboxAddr + 0x10]
    set appletAddrArgv3     [expr $appletMailboxAddr + 0x14]

    set maxBufferSize [expr $GENERIC::appletBufferSize]
    # Sanity check: buffer to write should not exceed the whole memory size    
    if { [expr $offset + $sizeToWrite] > $GENERIC::memorySize } {
        error "File size exceed memory capacity ([format "0x%X" $GENERIC::memorySize] bytes)"
    }
    
    # Init the ping pong algorithm: the buffer is active
    set bufferAddress $GENERIC::appletBufferAddress
    
    # Save the size of file to be sent
    set fileSize $sizeToWrite

    # Write data page after page...
    while {$sizeToWrite > 0} {
        # Update Status Lable
        GENERIC::UpdateStatusLabel $sizeToWrite $fileSize

        # Adjust the packet size to be sent
        if {$sizeToWrite < $maxBufferSize} {
            set bufferSize $sizeToWrite
        } else {
            set bufferSize $maxBufferSize
        }
        
        # Read Data From Input File
        set rawData [read $File $bufferSize]
    
        puts "-I- \tWriting: [format "0x%X" $bufferSize] bytes at [format "0x%X" $offset] (buffer addr : [format "0x%X" $bufferAddress])"
    
        # Copy in RAM the content of the page to be written
        TCL_Write_Data $target(handle) $bufferAddress rawData $bufferSize dummy_err
        
        # If this is a boot file modify 6th vector with file size
        if {[expr ($isBootFile == 1) && ($offset == 0)]} {
            TCL_Write_Int $target(handle) $sizeToWrite [expr $bufferAddress + (5 * 4)] dummy_err
        }
        
        # Write the Cmd op code in the argument area
        if {[catch {TCL_Write_Int $target(handle) $appletCmd(write) $appletAddrCmd} dummy_err] } {
            error "[format "0x%08x" $dummy_err]"
        }
        # Write the buffer address in the argument area
        if {[catch {TCL_Write_Int $target(handle) $bufferAddress $appletAddrArgv0} dummy_err] } {
            error "[format "0x%08x" $dummy_err]"
        }
        # Write the buffer size in the argument area
        if {[catch {TCL_Write_Int $target(handle) $bufferSize $appletAddrArgv1} dummy_err] } {
            error "[format "0x%08x" $dummy_err]"
        }
        # Write the memory offset in the argument area
        if {[catch {TCL_Write_Int $target(handle) $offset $appletAddrArgv2} dummy_err] } {
            error "[format "0x%08x" $dummy_err]"
        }

        # Launch the applet Jumping to the appletAddr
        if {[catch {set result [GENERIC::Run $appletCmd(write)]} dummy_err]} {
            error "[format "0x%08x" $dummy_err]"
        }
        switch $result {
            0 {
                # APPLET_SUCCESS
                # Retrieve how many bytes have been written
                set sizeWritten [TCL_Read_Int $target(handle) $appletAddrArgv0]
                
                puts "-I- \t[format "0x%X" $sizeWritten] bytes written by applet"
                
                # If all the buffer has not been written, move back to the first un-written byte offset
                if {$sizeWritten < $bufferSize} {
                    seek $File [expr $sizeWritten - $bufferSize] current
                }
                
                incr sizeToWrite [expr -$sizeWritten]
                incr offset $sizeWritten
            }
            
            1 {
                # APPLET_DEV_UNKNOWN
                error "[format "0x%08x" $result]"
            }
            
            9 {
                # APPLET_BAD_BLOCK
                # BAD block strategy : block is skipped and we write the next block with same data

                # Retrieve how many bytes have been written (must be 0)
                set sizeWritten  [TCL_Read_Int $target(handle) $appletAddrArgv0]
                
                puts "-I- \t[format "0x%X" $sizeWritten] bytes written by applet"
                
                # If all the buffer has not been written, move back to the first un-written byte offset
                seek $File [expr -$bufferSize] current
                
                incr offset $maxBufferSize
            }

            default {
                # All other errors
                error "[format "0x%08x" $result]"
            }
        }
    }

    return 1
}

#===============================================================================
#  proc GENERIC::Read
#-------------------------------------------------------------------------------
proc GENERIC::Read { offset sizeToRead File } {
    global target
    variable appletArg
    variable appletCmd
    variable appletAddr
    variable appletMailboxAddr
    variable appletBufferAddress
    variable appletBufferSize
    variable stepSize
    
    set dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArgv0     [expr $appletMailboxAddr + 0x08]
    set appletAddrArgv1     [expr $appletMailboxAddr + 0x0c]
    set appletAddrArgv2     [expr $appletMailboxAddr + 0x10]
    set appletAddrArgv3     [expr $appletMailboxAddr + 0x14]

    set maxBufferSize [expr $GENERIC::appletBufferSize]

    # Sanity check: buffer to read should not exceed the whole memory size    
    if { [expr $offset + $sizeToRead] > $GENERIC::memorySize } {
        error "File size exceed memory capacity ([format "0x%X" $GENERIC::memorySize] bytes)"
    }
    
    # Init the ping pong algorithm: the buffer is active
    set bufferAddress $GENERIC::appletBufferAddress
    
    # Save the size of file to be received
    set fileSize $sizeToRead
    
    # Write data page after page...
    while {$sizeToRead > 0} {
        # Update Status Lable
        GENERIC::UpdateStatusLabel $sizeToRead $fileSize

        # Adjust the packet size to be sent
        if {$sizeToRead < $maxBufferSize} {
            set bufferSize $sizeToRead
        } else {
            set bufferSize $maxBufferSize
        }
        
        puts "-I- \tReading: [format "0x%X" $bufferSize] bytes at [format "0x%X" $offset] (buffer addr : [format "0x%X" $bufferAddress])"
    
         # Write the Cmd op code in the argument area
        if {[catch {TCL_Write_Int $target(handle) $appletCmd(read) $appletAddrCmd} dummy_err] } {
            error "[format "0x%08x" $dummy_err]"
        }
        # Write the buffer address in the argument area
        if {[catch {TCL_Write_Int $target(handle) $bufferAddress $appletAddrArgv0} dummy_err] } {
            error "[format "0x%08x" $dummy_err]"
        }
        # Write the buffer size in the argument area
        if {[catch {TCL_Write_Int $target(handle) $bufferSize $appletAddrArgv1} dummy_err] } {
            error "[format "0x%08x" $dummy_err]"
        }
        # Write the memory offset in the argument area
        if {[catch {TCL_Write_Int $target(handle) $offset $appletAddrArgv2} dummy_err] } {
            error "[format "0x%08x" $dummy_err]"
        }

        # Launch the applet Jumping to the appletAddr
        if {[catch {set result [GENERIC::Run $appletCmd(read)]} dummy_err]} {
            error "[format "0x%08x" $dummy_err]"
        }

        switch $result {
            0 {
                # APPLET_SUCCESS
                # Retrieve how many bytes have been read
                set sizeRead [TCL_Read_Int $target(handle) $appletAddrArgv0]
                
                # Write Data to Output File
                set rawData [TCL_Read_Data $target(handle) $bufferAddress $sizeRead dummy_err]
                puts -nonewline $File $rawData    

                incr sizeToRead [expr -$sizeRead]
                incr offset $sizeRead
            }
            
            1 {
                # APPLET_DEV_UNKNOWN
                error "[format "0x%08x" $result]"
            }
            
            9 {
                # APPLET_BAD_BLOCK
                # BAD block strategy : block is skipped and we read the next block
                # Retrieve how many bytes have been read (must be 0)
                set sizeRead [TCL_Read_Int $target(handle) $appletAddrArgv0]
                
                # No Data to write in output file
                incr offset $maxBufferSize
            }

            default {
                # All other errors
                error "[format "0x%08x" $result]"
            }
        }
    }

    return 1
}

#===============================================================================
#  proc GENERIC::Init
#-------------------------------------------------------------------------------
proc GENERIC::Init {memAppletAddr memAppletMbxAddr appletFileName {appletArgList 0}} {
    global target
    variable appletAddr
    variable appletMailboxAddr
    variable appletCmd

    # Update the current applet addresses
    set appletAddr          $memAppletAddr
    set appletMailboxAddr   $memAppletMbxAddr


    # Load the applet to the target
    if {[catch {GENERIC::LoadApplet $appletAddr $appletFileName} dummy_err]} {
        error "Applet $appletFileName can not be loaded"
    }

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArgv0     [expr $appletMailboxAddr + 0x08]
    set appletAddrArgv1     [expr $appletMailboxAddr + 0x0c]
    set appletAddrArgv2     [expr $appletMailboxAddr + 0x10]
    set appletAddrArgv3     [expr $appletMailboxAddr + 0x14]

    
    # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $appletCmd(init) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command\n$dummy_err"
    }

    set argIdx 0
    foreach arg $appletArgList {
        # Write the Cmd op code in the argument area
        if {[catch {TCL_Write_Int $target(handle) $arg [expr $appletAddrArgv0 + $argIdx]} dummy_err] } {
            error "Error Writing Applet argument $arg ($dummy_err)"
        }
        incr argIdx 4
    }
    
    # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $appletCmd(init)]} dummy_err]} {
        error "Applet Init command has not been launched ($dummy_err)"
    }
    if {$result == 1} {
        error "Can't detect known device"
    } elseif {$result != 0} {
        error "Applet Init command returns error: [format "0x%08x" $result]"
    }
        
    # Retrieve values
    variable memorySize
    variable appletBufferAddress
    variable appletBufferSize
    set GENERIC::memorySize           [format "0x%X" [TCL_Read_Int $target(handle) $appletAddrArgv0]]
    set GENERIC::appletBufferAddress [TCL_Read_Int $target(handle) $appletAddrArgv1]
    set GENERIC::appletBufferSize    [TCL_Read_Int $target(handle) $appletAddrArgv2]
    set GENERIC::nandflashCurParam   [TCL_Read_Int $target(handle) $appletAddrArgv3]
    
    set FLASH::flashLockRegionSize [expr [TCL_Read_Int $target(handle) $appletAddrArgv3] & 0xFFFF]
    set FLASH::flashNumbersLockBits  [expr [TCL_Read_Int $target(handle) $appletAddrArgv3] >> 16]
    set FLASH::flashSize $GENERIC::memorySize

    puts "-I- Memory Size : [format "0x%X" $GENERIC::memorySize] bytes"
    puts "-I- Buffer address : [format "0x%X" $GENERIC::appletBufferAddress]"
    puts "-I- Buffer size: [format "0x%X" $GENERIC::appletBufferSize] bytes"
    
    puts "-I- Applet initialization done"
}

#===============================================================================
#  proc GENERIC::SendFile
#-------------------------------------------------------------------------------
proc GENERIC::SendFile {name addr {isBootFile 0}} {

    puts "GENERIC::SendFile $name at address [format "0x%X" $addr]"

    if { [catch {set f [open $name r]}] } {
        puts "-E- Can't open file $name"
        return
    }

    fconfigure $f -translation binary

    set size [file size $name]
    puts "-I- File size : [format "0x%X" $size] byte(s)"

    if {[catch {GENERIC::Write $addr $size $f $isBootFile} dummy_err]} {
        puts "-E- Can't send data ($dummy_err)"
    }
    close $f
}

#===============================================================================
#  proc GENERIC::ReceiveFile
#-------------------------------------------------------------------------------
proc GENERIC::ReceiveFile {name addr size} {

    puts "GENERIC::ReceiveFile $name : [format "0x%X" $size] bytes from address [format "0x%X" $addr]"

    # put data in a file
    if { [catch {set f2 [open $name w+]}] } {
        puts "-E- Can't open file $name"
        return -1
    }
    fconfigure $f2 -translation binary
    
    #read data from target
    if { [catch {GENERIC::Read $addr $size $f2} dummy_err] } {
        puts "-E- Can't receive data ($dummy_err)"
    }
    
    close $f2
}

#===============================================================================
#  proc GENERIC::EraseAll
#-------------------------------------------------------------------------------
proc GENERIC::EraseAll {{param 0}} {
    global target
    global softwareStatusLabelVariable
    variable appletMailboxAddr
    variable appletCmd

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArgv0     [expr $appletMailboxAddr + 0x08]
    set appletAddrArgv1     [expr $appletMailboxAddr + 0x0c]
    set appletAddrArgv2     [expr $appletMailboxAddr + 0x10]
    set appletAddrArgv3     [expr $appletMailboxAddr + 0x14]

    # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $appletCmd(erase) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }

    # Write the parameter in the argument area
    if {[catch {TCL_Write_Int $target(handle) $param $appletAddrArgv0} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }

    set softwareStatusLabelVariable "Full Erase in progress ..."

    puts "-I- GENERIC::EraseAll"

    # Run the applet
    if {[catch {set result [GENERIC::Run $appletCmd(erase)]} dummy_err]} {
        set softwareStatusLabelVariable ""
        error "Applet Erase command has not been launched ($dummy_err)"
    }

    set softwareStatusLabelVariable ""

    if {$result != 0} {
         error "[format "0x%08x" $dummy_err]"
    }
}

#===============================================================================
#  proc GENERIC::SendBootFileGUI
#-------------------------------------------------------------------------------
proc GENERIC::SendBootFileGUI {} {
    global softwareStatusLabelVariable
    global backupDirPath
    global conWindows
    

    set fileName [tk_getOpenFile -parent $conWindows -initialdir  $backupDirPath -defaultextension ".bin" -filetypes {{"Bin Files" {.bin}} {"All Files" {*.*}}}]
    if {$fileName == ""} {
        puts "-E- No File Selected"
        return
    }
    
    if { [catch {set size [file size $fileName]}] } {
        puts "-E- Can't open file $fileName"
        return
    }
    
    if { $size > $BOARD::maxBootSize } {
        puts "-E- Unauthorized Boot File Size"
        return
    }
    
    set softwareStatusLabelVariable "Sending data ..."

    # Send the file to the target (modifying the 6th vector)
    GENERIC::SendFile $fileName 0x0 1

    #Close the wait window
    set softwareStatusLabelVariable ""

    # Store the current dir
    set backupDirPath [file dirname $fileName]
}

#===============================================================================
#  proc GENERIC::SendBootFile
#-------------------------------------------------------------------------------
proc GENERIC::SendBootFile {name} {
    GENERIC::SendFile $name 0x0 1
}


################################################################################
################################################################################
## NAMESPACE RAM
################################################################################
################################################################################
namespace eval RAM {
    # Following variables are defined in <board>.tcl
    variable appletAddr
    variable appletMailboxAddr
    variable appletFileName
}

#===============================================================================
#  proc RAM::sendFile
#-------------------------------------------------------------------------------
proc RAM::sendFile { name addr } {
    
    global valueOfDataForSendFile
    global target
    set dummy_err 0

    if {[catch {set f [open $name r]}]} {
        set valueOfDataForSendFile 0
        puts "-E- Can't open file $name"
        return -1
    }
    
    fconfigure $f -translation binary
    
    set size [file size $name]
    puts "-I- File size = $size byte(s)"
    set valueOfDataForSendFile [read $f $size]
    
    close $f

    if {[catch {TCL_Write_Data $target(handle) $addr valueOfDataForSendFile $size dummy_err}]} {
        puts "-E- Can't send data, error in connection"
        set valueOfDataForSendFile 0
        return
    }
    
    set valueOfDataForSendFile 0
}

#===============================================================================
#  proc RAM::receiveFile
#-------------------------------------------------------------------------------
proc RAM::receiveFile {name addr size} {

    global target
    set dummy_err 0

    #read data from target
    if {[catch {set result [TCL_Read_Data $target(handle) $addr $size dummy_err]}]} {
        puts "-E- Can't read data, error in connection"
        return -1
    }

    # put data in a file
    if {[catch {set f2 [open $name w+]}]} {
        puts "-E- Can't open file $name"
        return -1
    }

    fconfigure $f2 -translation binary
    puts -nonewline $f2 $result
    close $f2
}


################################################################################
## NAMESPACE DATAFLASH
################################################################################
namespace eval DATAFLASH {
    # Following variables are defined in <board>.tcl
    variable appletAddr
    variable appletMailboxAddr
    variable appletFileName
    variable DATAFLASH_initialized 0
}

#===============================================================================
#  proc DATAFLASH::Init
#-------------------------------------------------------------------------------
proc DATAFLASH::Init {dfId} {
    global target
    variable appletAddr
    variable appletMailboxAddr
    variable appletFileName
    variable DATAFLASH_initialize

    set DATAFLASH_initialized 0

    puts "-I- DATAFLASH::Init $dfId (trace level : $target(traceLevel))"
    
    # Load the applet to the target
    if {[catch {GENERIC::Init $DATAFLASH::appletAddr $DATAFLASH::appletMailboxAddr $DATAFLASH::appletFileName [list $target(comType) $target(traceLevel) $dfId ]} dummy_err] } {
        error "Error Initializing DataFlash Applet ($dummy_err)"
    }

    set DATAFLASH_initialized 1
}

#===============================================================================
#  proc DATAFLASH::EraseAll
#-------------------------------------------------------------------------------
proc DATAFLASH::EraseAll {} {
    global target
    global softwareStatusLabelVariable
    variable appletMailboxAddr
    
    set dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArgv0     [expr $appletMailboxAddr + 0x08]
    set appletAddrArgv1     [expr $appletMailboxAddr + 0x0c]
    set appletAddrArgv2     [expr $appletMailboxAddr + 0x10]
    set appletAddrArgv3     [expr $appletMailboxAddr + 0x14]
    
    set softwareStatusLabelVariable "Full Erase in progress ..."
    
    set sizeToErase $GENERIC::memorySize
    set eraseOffset 0
    
    # Save the size of memory to be erased
    set fileSize $sizeToErase
    
    while {$sizeToErase > 0} {
        # Update Status Lable
        GENERIC::UpdateStatusLabel $sizeToErase $fileSize
        
        puts "-I- \tErasing: [format "0x%X"  $GENERIC::appletBufferSize] bytes at address [format "0x%X" $eraseOffset]"
        # Write the Cmd op code in the argument area
        if {[catch {TCL_Write_Int $target(handle) $GENERIC::appletCmd(erasebuffer) $appletAddrCmd} dummy_err] } {
            set softwareStatusLabelVariable ""
            error "Error Writing Applet command ($dummy_err)"
        }
        # Write the buffer address in the argument area
        if {[catch {TCL_Write_Int $target(handle) $eraseOffset $appletAddrArgv0} dummy_err] } {
            set softwareStatusLabelVariable ""
            error "Error Writing Applet erase all \n$dummy_err"
        }
        # Launch the applet Jumping to the appletAddr
        if {[catch {set result [GENERIC::Run $GENERIC::appletCmd(erasebuffer)]} dummy_err]} {
            set softwareStatusLabelVariable ""
            error "Applet erase all command has not been launched ($dummy_err)"
        }
        incr eraseOffset $GENERIC::appletBufferSize
        set sizeToErase  [expr $sizeToErase - ($GENERIC::appletBufferSize)]
    }
    set softwareStatusLabelVariable ""
}

#===============================================================================
#  proc DATAFLASH::BinaryPage
#-------------------------------------------------------------------------------
proc DATAFLASH::BinaryPage {} {
    global target
    global commandLineMode
    variable appletMailboxAddr
    set dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArgv0     [expr $appletMailboxAddr + 0x08]
    set appletAddrArgv1     [expr $appletMailboxAddr + 0x0c]
    set appletAddrArgv2     [expr $appletMailboxAddr + 0x10]
    set appletAddrArgv3     [expr $appletMailboxAddr + 0x14]
    
    
    if {$commandLineMode == 0} {
        # Confirm to set the Binary Page
        set answer [tk_messageBox -title "Power-of-2 page configuration"\
        -message "The power-of-2 page size is a onetime programmable configuration register \
        and once the device is configured for power-of-2 page size, it cannot be reconfigured again" \
        -icon question -type yesno \
        -detail "Do you want to configure binary page? \"Yes\" Config it"]
        switch -- $answer {
           yes { puts "Config power-of-2 page" }
           no { return }
        }
    }
    
     # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $GENERIC::appletCmd(binarypage) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }
    
    # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $GENERIC::appletCmd(binarypage)]} dummy_err]} {
        error "Applet set binarypage command has not been launched ($dummy_err)"
    }
    
    if {$commandLineMode == 0} {
        set answer [tk_messageBox -title "Power-of-2 page configuration done"\
        -message "Please power down and power up board again \n\r The page for the binary page size can then be programmed" \
        -icon warning -type ok ]
    }
    puts "-I- Power-0f-2 BInary Page Configured"
    
}


################################################################################
## NAMESPACE SERIALFLASH
################################################################################
namespace eval SERIALFLASH {
    # Following variables are defined in <board>.tcl
    variable appletAddr
    variable appletMailboxAddr
    variable appletFileName
}

#===============================================================================
#  proc SERIALFLASH::Init
#-------------------------------------------------------------------------------
proc SERIALFLASH::Init {sfId} {
    global target
    variable appletAddr
    variable appletMailboxAddr
    variable appletFileName

    puts "-I- SERIALFLASH::Init $sfId (trace level : $target(traceLevel))"
    
    # Load the applet to the target
    GENERIC::Init $SERIALFLASH::appletAddr $SERIALFLASH::appletMailboxAddr $SERIALFLASH::appletFileName [list $target(comType) $target(traceLevel) $sfId]
}

#===============================================================================
#  proc SERIALFLASH::EraseAll
#-------------------------------------------------------------------------------
proc SERIALFLASH::EraseAll {} {
    global target
    global softwareStatusLabelVariable
    variable appletMailboxAddr

    set dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArgv0     [expr $appletMailboxAddr + 0x08]
    set appletAddrArgv1     [expr $appletMailboxAddr + 0x0c]
    set appletAddrArgv2     [expr $appletMailboxAddr + 0x10]
    set appletAddrArgv3     [expr $appletMailboxAddr + 0x14]
    
    set softwareStatusLabelVariable "Full Erase in progress ..."
    
    set sizeToErase $GENERIC::memorySize
    set eraseOffset 0
    
    # Save the size of memory to be erased
    set fileSize $sizeToErase
    
    while {$sizeToErase > 0} {
        # Update Status Lable
        GENERIC::UpdateStatusLabel $sizeToErase $fileSize
        
        puts "-I- \tErasing one block at address [format "0x%X" $eraseOffset]"
        # Write the Cmd op code in the argument area
        if {[catch {TCL_Write_Int $target(handle) $GENERIC::appletCmd(erasebuffer) $appletAddrCmd} dummy_err] } {
            set softwareStatusLabelVariable ""
            error "Error Writing Applet command ($dummy_err)"
        }
        # Write the buffer address in the argument area
        if {[catch {TCL_Write_Int $target(handle) $eraseOffset $appletAddrArgv0} dummy_err] } {
            set softwareStatusLabelVariable ""
            error "Error Writing Applet erase all \n$dummy_err"
        }
        # Launch the applet Jumping to the appletAddr
        if {[catch {set result [GENERIC::Run $GENERIC::appletCmd(erasebuffer)]} dummy_err]} {
            set softwareStatusLabelVariable ""
            error "Applet erase all command has not been launched ($dummy_err)"
        }
        # Retrieve how many bytes have been written
        set sizeErased  [TCL_Read_Int $target(handle) $appletAddrArgv0]
        incr eraseOffset $sizeErased 
        set sizeToErase  [expr $sizeToErase - $sizeErased ]
        puts "-I- \t[format "0x%X" $sizeErased] bytes erased"
    }
    set softwareStatusLabelVariable ""
}




#===============================================================================
#  proc SERIALFLASH::EraseAll
#-------------------------------------------------------------------------------
proc SERIALFLASH::Xip {} {
    global target
    variable appletMailboxAddr
    variable appletCmd

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
   

    # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $GENERIC::appletCmd(qspixip) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }

    puts "-I- Execute from QSPI flash, sam-ba will be halted..."

    # Run the applet
    GENERIC::Run  $GENERIC::appletCmd(qspixip)

}

################################################################################
## NAMESPACE OWEEPROM
################################################################################
namespace eval OW {
    # Following variables are defined in <board>.tcl
    variable appletAddr
    variable appletMailboxAddr
    variable appletFileName
    variable deviceList
    variable isDeviceFound 0
}

#===============================================================================
#  proc OW::Init
#-------------------------------------------------------------------------------
proc OW::Init {} {
    global target
    variable appletAddr
    variable appletMailboxAddr
    variable appletFileName
    variable deviceList
    variable isDeviceFound
    
    puts "-I- OW::Init (trace level : $target(traceLevel))"
    
    # Load the applet to the target
    GENERIC::Init $OW::appletAddr $OW::appletMailboxAddr $OW::appletFileName [list $target(comType) $target(traceLevel)]
        
    set numOfDevices        [TCL_Read_Int $target(handle) [expr $appletMailboxAddr + 0x14]]
    set deviceInfoAddr      [TCL_Read_Int $target(handle) [expr $appletMailboxAddr + 0x18]]
    
    puts "-I- Found [format "%d" $numOfDevices] devices"
    
    # Clean up the device list
    if {$isDeviceFound == 1} {
        unset deviceList
        set isDeviceFound 0
    }

    for {set i 1} {$i <= $numOfDevices} {incr i 1} {
    
        # Read family code to get memory size
        set familyCode  [TCL_Read_Byte $target(handle) $deviceInfoAddr]
        if {$familyCode == 0x2D} { # DS2431 series
            set memSize 0x88
        } elseif {$familyCode == 0x23} { # DS2433 series
            set memSize 0x200
        } else {
            puts "-E- Unknown Device"
            set memSize 0x0
        }
        
        set lowSerialNo [format "%08x" [TCL_Read_Int $target(handle) $deviceInfoAddr]]
        set highSerialNo [format "%08x" [TCL_Read_Int $target(handle) [expr $deviceInfoAddr + 4]]]
        
        lappend deviceList $highSerialNo$lowSerialNo
        
        puts "-I- Device [format "%d" $i]: $highSerialNo$lowSerialNo"
        puts "-I- Memory Size: 0x[format "%x" $memSize] bytes"
        incr deviceInfoAddr 8
    }

    puts "-I- Please select the target device before reading/writing the memory"
    set isDeviceFound 1
}

#===============================================================================
#  proc OW::SelectDevice
#-------------------------------------------------------------------------------
proc OW::SelectDevice {{deviceSN 0}} {
    global target 
    global commandLineMode
    variable appletMailboxAddr
    variable deviceList
    variable isDeviceFound

    if {$isDeviceFound == 0} {
        error "No device found"
    }
    
    set lowDeviceSNAddr [expr $appletMailboxAddr + 0x14]
    set highDeviceSNAddr [expr $appletMailboxAddr + 0x18]
    
    # Get target device serial number
    if {$commandLineMode == 0} {
        set targetDeviceNo [owdlg $deviceList]
    } else {
        if {[lsearch -exact $deviceList $deviceSN] != -1} {
            set targetDeviceNo $deviceSN
        } else {
            puts "-E- Target device (SN: $deviceSN) does not exist."
            puts "-I- Device found: $deviceList"
            error "Device not found"
        }
    }

    set lowDeviceSN    0x[string range $targetDeviceNo 8 15]
    set highDeviceSN   0x[string range $targetDeviceNo 0 7]
    set familyCode     0x[string range $targetDeviceNo 14 15]
    
    if {$familyCode == 0x2D} {
        set GENERIC::memorySize 0x88
    } elseif {$familyCode == 0x23} {
        set GENERIC::memorySize 0x200
    } else {
        set GENERIC::memorySize 0x0
        error "Unknown family code: $familyCode "
    }
    
    puts "-I- Target Device No. $targetDeviceNo"
    puts "-I- Memory Size: $GENERIC::memorySize bytes"
    
    if {[catch {TCL_Write_Int $target(handle) $lowDeviceSN $lowDeviceSNAddr} dummy_err] } {
        error "Error lower 8-byte serial number: $lowDeviceSNAddr"
    }

    if {[catch {TCL_Write_Int $target(handle) $highDeviceSN $highDeviceSNAddr} dummy_err] } {
        error "Error higher 8-byte serial number: $highDeviceSNAddr"
    }
}

################################################################################
## NAMESPACE EEPROM
################################################################################
namespace eval EEPROM {
    # Following variables are defined in <board>.tcl
    variable appletAddr
    variable appletMailboxAddr
    variable appletFileName
}

proc EEPROM::Init {deviceId {param 0}} {
    global target
    variable appletAddr
    variable appletMailboxAddr
    variable appletFileName

    puts "-I- EEPROM::Init $deviceId $param (trace level : $target(traceLevel))"
    
    # Load the applet to the target
    GENERIC::Init $EEPROM::appletAddr $EEPROM::appletMailboxAddr $EEPROM::appletFileName [list $target(comType) $target(traceLevel) $deviceId $param]
}


################################################################################
## NAMESPACE NANDFLASH
################################################################################
namespace eval NANDFLASH {
    # Following variables are defined in <board>.tcl
    variable appletAddr
    variable appletMailboxAddr
    variable appletFileName

    # Flags to force the erase operaton on block even tagged as bad
    variable scrubErase     0xEA11
    variable normalErase    0x0
}

#===============================================================================
#  proc NANDFLASH::Init
#-------------------------------------------------------------------------------
proc NANDFLASH::Init {} {
    global target
    global chip_id
    global bootHeaderValue
    variable appletAddr
    variable appletMailboxAddr
    variable appletFileName

    puts "-I- NANDFLASH::Init (trace level : $target(traceLevel))"
    # Load the applet to the target
    GENERIC::Init $NANDFLASH::appletAddr $NANDFLASH::appletMailboxAddr $NANDFLASH::appletFileName [list $target(comType) $target(traceLevel)]
    if {($target(board) == "at91sam9g15-ek") || 
        ($target(board) == "at91sam9g25-ek") ||
        ($target(board) == "at91sam9g35-ek") ||
        ($target(board) == "at91sam9x25-ek") ||
        ($target(board) == "at91sam9x35-ek")} {
        puts " - By default PMECC is activated, 
    - By default, The pmecc computation is based on a sector of 512 bytes,
    - By default, correcting capability for pmecc is retrieved from ONFI parameter,
    - By default, offset of the first ecc byte in spare zone is '2',
    - To config pmecc parameter, using 'NANDFLASH::SetNandHeaderValue pmeccParam pmeccParamValue' command,
       - Type  'NANDFLASH::SetNandHeaderValue '  to dispaly current pmecc configuration.
       - Type  'NANDFLASH::SetNandHeaderValue ?'  to get help for pmecc setting,
- To active software ECC, using 'Enable Software ECC' command,
    - Recommand to erase all after the ecc mode switch between software ECC & pmecc."
    }
    set GENERIC::nandflashInitialized 1
    set GENERIC::nandflashEccStatus 2
    set bootHeaderValue(trim) 0
}


#===============================================================================
#  proc NANDFLASH::EnableSoftwareEcc
#-------------------------------------------------------------------------------
proc NANDFLASH::EnableSoftwareEcc { offset } {
    if { $GENERIC::nandflashEccStatus == 1} {
       puts "-I- Software Ecc is already enabled"
       return 1
    }
    # Launch the SwitchEccMode.
    set dummy_err 0
    if {[catch {set result [NANDFLASH::SwitchEccMode 0 $offset]} dummy_err]} {
        error "SwitchEccMode command has not been launched ($dummy_err)"
    }
    if { $result == 0 } {
        puts "-I- Software Ecc is enabled"
        set GENERIC::nandflashEccStatus 1
        return 1
    } else {
        puts "-I- Enable Software failed"
        return -1
    }
}

#===============================================================================
#  proc NANDFLASH::DisableSoftwareEcc
#-------------------------------------------------------------------------------
proc NANDFLASH::DisableSoftwareEcc { } {
    if { $GENERIC::nandflashEccStatus == 0} {
       puts "-I- Software Ecc is already disabled"
       return 1
    }
    # Launch the SwitchEccMode.
    set dummy_err 0
    if {[catch {set result [NANDFLASH::SwitchEccMode 1]} dummy_err]} {
        error "SwitchEccMode command has not been launched ($dummy_err)"
    }
    if { $result == 0 } {
        puts "-I- Software Ecc disabled"
        puts "-W- Do not recommend to access Nand Flash without ecc!"
        set GENERIC::nandflashEccStatus 0
        return 1
    } else {
        puts "-I- Software Ecc disable failed"
        return -1
    }
}

#===============================================================================
#  proc NANDFLASH::EnablePmecc
#-------------------------------------------------------------------------------
proc NANDFLASH::EnablePmecc { } {
    if { $GENERIC::nandflashEccStatus == 2} {
       puts "-I- Pmecc is already enabled"
       return 1
    }
    # Launch the SwitchEccMode.
    set dummy_err 0
    if {[catch {set result [NANDFLASH::SwitchEccMode 2]} dummy_err]} {
        error "SwitchEccMode command has not been launched ($dummy_err)"
    }
    if { $result == 0 } {
        puts "-I- Pmecc is enabled"
        set GENERIC::nandflashEccStatus 2
        return 1
    } else {
        puts "-I- Enable pmecc failed!"
        return -1
    }
}

#===============================================================================
#  proc NANDFLASH::DisablePmecc
#-------------------------------------------------------------------------------
proc NANDFLASH::DisablePmecc { } {
    if { $GENERIC::nandflashEccStatus == 0} {
       puts "-I- Pmecc is already disabled"
       return 1
    }
    # Launch the SwitchEccMode.
    set dummy_err 0
    if {[catch {set result [NANDFLASH::SwitchEccMode 3]} dummy_err]} {
        error "SwitchEccMode command has not been launched ($dummy_err)"
    }
    if { $result == 0 } {
        puts "-I- Pmecc disabled"
        puts "-W- Do not recommend to access Nand Flash without ecc!"
        set GENERIC::nandflashEccStatus 0
        return 1
    } else {
        puts "-I- Pmecc disable failed!"
        return -1
    }
}

#===============================================================================
#  proc NANDFLASH::EnableInternalEcc
#-------------------------------------------------------------------------------
proc NANDFLASH::EnableInternalEcc {} {
    if { $GENERIC::nandflashEccStatus == 3} {
       puts "-I- Internal Ecc is already enabled"
       return 1
    }
    # Launch the SwitchEccMode.
    set dummy_err 0
    if {[catch {set result [NANDFLASH::SwitchEccMode 4]} dummy_err]} {
        error "SwitchEccMode command has not been launched ($dummy_err)"
    }
    if { $result == 0 } {
        puts "-I- Internal ecc is enabled"
        set GENERIC::nandflashEccStatus 3
        return 1
    } else {
        puts "-I- Enable Micron Nandflash with internal ecc failed!"
        return -1
    }
}

#===============================================================================
#  proc NANDFLASH::SwitchEccMode
#-------------------------------------------------------------------------------
proc NANDFLASH::SwitchEccMode {mode {offset 0} } {
    global target
    global bootHeaderValue
    variable appletAddr
    variable appletMailboxAddr
    variable appletFileName
    if { $GENERIC::nandflashInitialized == 0} {
        puts "-E- Nand flash not initialized!"
        return -1
    }
    set dummy_err 0
    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArgv0     [expr $appletMailboxAddr + 0x08]
    set appletAddrArgv1     [expr $appletMailboxAddr + 0x0c]

    # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $GENERIC::appletCmd(switchEccMode) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }
    # Write the mode for APPLET_CMD_SWITCH_ECC command in the argument area
    if {[catch {TCL_Write_Int $target(handle) $mode $appletAddrArgv0} dummy_err] } {
        error "Error Writing Applet mode  \n$dummy_err"
    }

    if { $mode == 0} {
        # Write the ecc offset (spare size > 64) in the argument area
        if {[catch {TCL_Write_Int $target(handle) $offset $appletAddrArgv1} dummy_err] } {
            error "Error Writing Applet mode  \n$dummy_err"
        }
    }
    # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $GENERIC::appletCmd(switchEccMode)]} dummy_err]} {
        error "Applet switchEccMode command has not been launched ($dummy_err)"
    }
    return $result
}

#===============================================================================
# NANDFLASH::NandDisplayHeaderValue 
#===============================================================================
proc NANDFLASH::NandDisplayHeaderValue {paramIndex paramValue} {
    if { $paramIndex != "usePmecc" && $paramIndex != "sectorPerPage" && $paramIndex != "spareSize" 
         && $paramIndex != "eccBitReq" && $paramIndex != "sectorSize" && $paramIndex != "eccOffset" 
            && $paramIndex != "HEADER" } {
        puts " - unknow command "
        return;
    }

    if { $paramIndex == "usePmecc" } {
        if {$paramValue == 0} {
            puts "   - no Pmecc, value = [format "0x%X" $paramValue]" 
        } else {
            puts "   - use Pmecc, value = [format "0x%X" $paramValue]" 
        }
    }
    if { $paramIndex == "sectorPerPage" } {
        switch $paramValue {
            0 {
                puts "   - 1 sectors of data per page, value = [format "0x%X" $paramValue]" 
            }
            1 {
                puts "   - 2 sectors of data per page, value = [format "0x%X" $paramValue]" 
            }
            2 {
                puts "   - 4 sectors of data per page, value = [format "0x%X" $paramValue]" 
            }
            3 {
                puts "   - 8 sectors of data per page, value = [format "0x%X" $paramValue]" 
            }
            default {
                puts " -unknow value"
            }
        }
    }
    if { $paramIndex == "spareSize" } {
        puts "   - spare zone in bytes is $paramValue, value = [format "0x%X" $paramValue]" 
    }
    if { $paramIndex == "eccBitReq" } {
        switch $paramValue {
            0 {
                puts "   - 2 bits of errors per sector, value = [format "0x%X" $paramValue]" 
            }
            1 {
                puts "   - 4 bits of errors per sector, value = [format "0x%X" $paramValue]" 
            }
            2 {
                puts "   - 8 bits of errors per sector, value = [format "0x%X" $paramValue]" 
            }
            3 {
                puts "   - 12 bits of errors per sector, value = [format "0x%X" $paramValue]" 
            }
            4 {
                puts "   - 24 bits of errors per sector, value = [format "0x%X" $paramValue]" 
            }
            default {
                puts "   - unknow value"
            }
        }
    }
    if { $paramIndex == "sectorSize" } {
        switch $paramValue {
            0 {
                puts "   - The PMECC computation is based on a sector of 512 bytes , value = [format "0x%X" $paramValue]" 
            }
            1 {
                puts "   - The PMECC computation is based on a sector of 1024 bytes , value = [format "0x%X" $paramValue]" 
            }
            default {
                puts "   - unknow value"
            }
        }
    }
    if { $paramIndex == "eccOffset" } {
        puts "   - offset of the first ecc byte in spare zone is $paramValue, value = [format "0x%X" $paramValue]"
    }
    if { $paramIndex  == "HEADER" } {
        puts "   - HEADER value  is [format "0x%X" $paramValue]"
    }
}

#===============================================================================
# NANDFLASH::NandSetTrimffs 
#===============================================================================
proc NANDFLASH::NandSetTrimffs {mode} {
global target
    variable appletAddr
    variable appletMailboxAddr
    variable appletFileName
    if { $GENERIC::nandflashInitialized == 0} {
        puts "-E- Nand flash not initialized!"
        return -1
    }
    set dummy_err 0
    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArgv0     [expr $appletMailboxAddr + 0x08]

    # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $GENERIC::appletCmd(trimffsMode) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }
    # Write the mode for APPLET_CMD_SWITCH_ECC command in the argument area
    if {[catch {TCL_Write_Int $target(handle) $mode $appletAddrArgv0} dummy_err] } {
        error "Error Writing Applet mode  \n$dummy_err"
    }
    # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $GENERIC::appletCmd(trimffsMode)]} dummy_err]} {
        error "Applet Trimffs command has not been launched ($dummy_err)"
    }
    return $result
}

#===============================================================================
# NANDFLASH::NandHeaderValue 
#===============================================================================
proc NANDFLASH::NandHeaderValue {args} {
    global target
    global bootHeaderValue
    global commandLineMode
    variable appletAddr
    variable appletMailboxAddr
    variable appletFileName
    variable headerValue
    

    if { $GENERIC::nandflashInitialized == 0} {
        puts "-E- Nand flash not initialized!"
        return -1
    }
    set curParamHeader $GENERIC::nandflashCurParam
    set usePmecc 0
    set dummy_err 0
    set pmeccIF   0
    if { [llength $args] == 2 } {
            set paramIndex [lindex $args 0]
            set paramValue [lindex $args 1]
            if { $paramIndex == "HEADER"} {
                set curParamHeader $paramValue
                set pmeccIF 1
            }
    }
    if {$commandLineMode == 0 && $pmeccIF != 1} {
       set bootHeaderValue(eccType) $GENERIC::nandflashEccStatus
       set bootHeaderValue(usePmecc) [expr $curParamHeader & 0x1]
       set bootHeaderValue(nbSectorPerPage) [expr [expr $curParamHeader & 0xe] >> 1]
       set bootHeaderValue(spareSize) [expr [expr $curParamHeader & 0x1FF0] >> 4]
       set bootHeaderValue(eccBitReq) [expr [expr $curParamHeader & 0xE000] >> 13]
       set bootHeaderValue(sectorSize) [expr [expr $curParamHeader & 0x30000] >> 16]
       set bootHeaderValue(eccOffset) [expr [expr $curParamHeader & 0x7FC0000] >> 18]
       
       set returnValue [bootheaderDialg]
       if {$returnValue == 0} {
          puts "Ecc type is $bootHeaderValue(eccType) Ecc Status is $GENERIC::nandflashEccStatus"

          switch $bootHeaderValue(eccType) {
              0 {# Ecc status: 0= ECC_NO, 1= ECC_SOFT, 2=ECC_PMECC, 3=ECC_INTERNAL
                   if {$GENERIC::nandflashEccStatus == 1} {
                       puts "NANDFLASH::DisableSoftwareEcc "
                       NANDFLASH::DisableSoftwareEcc
                       return 1 
                   }
                   if {$GENERIC::nandflashEccStatus == 2} {
                       puts "NANDFLASH::DisablePmecc "
                       NANDFLASH::DisablePmecc
                       return 1 
                   }
              }
              1 {
                   if {$GENERIC::nandflashEccStatus == 2} {
                       puts "NANDFLASH::DisablePmecc "
                       puts "NANDFLASH::EnableSoftwareEcc "
                       puts [expr $bootHeaderValue(eccOffset)]
                       NANDFLASH::DisablePmecc
                       NANDFLASH::EnableSoftwareEcc $bootHeaderValue(eccOffset)
                       return 1 
                   }
                   if {($GENERIC::nandflashEccStatus == 1) } {
                       puts [expr $bootHeaderValue(eccOffset)]
                       NANDFLASH::EnableSoftwareEcc $bootHeaderValue(eccOffset)
                       return 1 
                   }
                   if {($GENERIC::nandflashEccStatus == 0) } {
                       NANDFLASH::EnableSoftwareEcc $bootHeaderValue(eccOffset)
                       return 1 
                   }
                }
              2 {
                   if {$GENERIC::nandflashEccStatus == 1} {
                       puts "NANDFLASH::DisableSoftwareEcc "
                       puts "NANDFLASH::EnablePmecc "
                       NANDFLASH::DisableSoftwareEcc
                       NANDFLASH::EnablePmecc
                   } 
                   if {$GENERIC::nandflashEccStatus == 0} {
                       puts "NANDFLASH::EnablePmecc "
                       NANDFLASH::EnablePmecc
                   }
                }
          }
          puts "-I- Configure trimffs $bootHeaderValue(trim)"
          NANDFLASH::NandSetTrimffs $bootHeaderValue(trim)
          set paramValue [expr [expr $bootHeaderValue(usePmecc) & 0x1] | \
          [expr [expr $bootHeaderValue(nbSectorPerPage) & 0x7] << 1] |\
          [expr [expr $bootHeaderValue(spareSize) & 0x1FF] << 4 ] | \
          [expr [expr $bootHeaderValue(eccBitReq) & 0x7] << 13 ] | \
          [expr [expr $bootHeaderValue(sectorSize) & 0x3] << 16 ] | \
          [expr [expr $bootHeaderValue(eccOffset) & 0x1FF] << 18] | \
          [expr 0x0c << 28 ]]
          puts "-I- PMECC [format "%x" $paramValue] to be Configured"
          set paramIndexforApplets  7
        } else {
            puts "-I- User canceled!"
            return -1
        }
    } else {
        if { [llength $args] == 0} {
            set usePmecc [expr $curParamHeader & 0x1]
            NANDFLASH::NandDisplayHeaderValue "usePmecc" $usePmecc
            set nbSectorPerPage [expr [expr $curParamHeader & 0xe] >> 1]
            NANDFLASH::NandDisplayHeaderValue "sectorPerPage"  $nbSectorPerPage
            set spareSize [expr [expr $curParamHeader & 0x1FF0] >> 4]
            NANDFLASH::NandDisplayHeaderValue "spareSize"  $spareSize
            set eccBitReq [expr [expr $curParamHeader & 0xE000] >> 13]
            NANDFLASH::NandDisplayHeaderValue "eccBitReq"  $eccBitReq
            set sectorSize [expr [expr $curParamHeader & 0x30000] >> 16]
            NANDFLASH::NandDisplayHeaderValue  "sectorSize" $sectorSize
            set eccOffset [expr [expr $curParamHeader & 0x7FC0000] >> 18]
            NANDFLASH::NandDisplayHeaderValue "eccOffset" $eccOffset
            puts ""
            NANDFLASH::NandDisplayHeaderValue "HEADER"  $curParamHeader
            return 1
        }
        if { [llength $args] == 1} {
            if { [lindex $args 0] != "usePmecc" &&
                 [lindex $args 0] != "sectorPerPage" &&
                 [lindex $args 0] != "spareSize" &&
                 [lindex $args 0] != "eccBitReq" &&
                 [lindex $args 0] != "sectorSize" &&
                 [lindex $args 0] != "eccOffset" &&
                 [lindex $args 0] != "?"} {
                 error "Unknown parameter [lindex $args 0]!"
                 return -1
            }
            if { [lindex $args 0] == "usePmecc" } {
                puts "NANDFLASH::NandHeaderValue usePmecc x (x = 0 no pmecc, x = 1 use pmecc)"
            }
            if { [lindex $args 0] == "sectorPerPage" } {
                puts "NANDFLASH::NandHeaderValue sectorPerPage x (x = 0|1|2|3 for 1|2|4|8 sectors of data per page)"        
            }
            if { [lindex $args 0] == "spareSize" } {
                puts "NANDFLASH::NandHeaderValue spareSize x (0<x<512, x is size of spare zone in bytes)"
            }
            if { [lindex $args 0] == "eccBitReq" } {
                puts "NANDFLASH::NandHeaderValue eccBitReq x (x = 0|1|2|3|4 for 2|4|8|12|24 bits of errors per sector)"
            }
            if { [lindex $args 0] == "sectorSize" } {
                puts "NANDFLASH::NandHeaderValue sectorSize x (x = 0|1  0: Pmecc sector size 512 bytes,1: Pmecc sector size 1024 bytes)"
            }
            if { [lindex $args 0] == "eccOffset" } {
                puts "NANDFLASH::NandHeaderValue eccOffset x (0<=x<512  x is offset of the first ecc byte in spare zone)"
            }
            if { [lindex $args 0] == "?" } {
                puts "Syntax:   NANDFLASH::NandHeaderValue {pmeccParam pmeccParamValue} "
                puts ""
                puts "NANDFLASH::NandHeaderValue usePmecc x (x = 0 no pmecc, x = 1 use pmecc)"
                puts "NANDFLASH::NandHeaderValue sectorPerPage x (x = 0|1|2|3 for 1|2|4|8 sectors of data per page)"
                puts "NANDFLASH::NandHeaderValue spareSize x (0<x<512, x is size of spare zone in bytes)"
                puts "NANDFLASH::NandHeaderValue eccBitReq x (x = 0|1|2|3|4 for 2|4|8|12|24 bits of errors per sector)"
                puts "NANDFLASH::NandHeaderValue sectorSize x (x = 0|1  0: Pmecc sector size 512 bytes,1: Pmecc sector size 1024 bytes)"
                puts "NANDFLASH::NandHeaderValue eccOffset x (0<=x<512  x is offset of the first ecc byte in spare zone)"
                puts ""
                puts "NANDFLASH::NandHeaderValue HEADER x (x is 32-bits-header, see 'NAND Flash Specific Header Detection' in datasheet)"
            } 
            return 1
        }
        if { [llength $args] == 2 } {
            set paramIndex [lindex $args 0]
            set paramValue [lindex $args 1]
            set err 0

            if { $paramIndex != "usePmecc" &&
                 $paramIndex != "sectorPerPage" &&
                 $paramIndex != "spareSize" &&
                 $paramIndex != "eccBitReq" &&
                 $paramIndex != "sectorSize" &&
                 $paramIndex != "eccOffset" &&
                 $paramIndex != "HEADER"} {
                 error "Unknown 1st parameter $paramIndex !"
                 return -1
            }
            NANDFLASH::NandDisplayHeaderValue $paramIndex $paramValue
            if { $paramIndex == "usePmecc" } {
                if { $paramValue != 0  && $paramValue != 1 } {
                   set err 1
                }
                set paramIndexforApplets  1
            }
            if { $paramIndex == "sectorPerPage" } {
                if { $paramValue > 3 } {
                   set err 1
                }
                set paramIndexforApplets  2
            }
            if { $paramIndex == "spareSize" } {
            if { $paramValue >= 512 } {
                   set err 1
                }
                set paramIndexforApplets  3
            }
            if { $paramIndex == "eccBitReq" } {
                if { $paramValue > 4 } {
                   set err 1
                }
                set paramIndexforApplets  4
            }
            if { $paramIndex == "sectorSize" } {
                if { $paramValue != 0  && $paramValue != 1 } {
                   set err 1
                }
                set paramIndexforApplets  5
            }
            if { $paramIndex == "eccOffset" } {
            if { $paramValue >= 512 } {
                   set err 1
                }
                set paramIndexforApplets  6
            }
            if { $paramIndex == "HEADER" } {
                set paramIndexforApplets  7
            }
            if {$err == 1} {
                puts "-I- Pmecc header configration failed!"
                return -1
            }
        }
    }
    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArgv0     [expr $appletMailboxAddr + 0x08]
    set appletAddrArgv1     [expr $appletMailboxAddr + 0x0c]

    # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $GENERIC::appletCmd(pmeccParam) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }
    # Write the paramIndex for APPLET_CMD_PMECC_HEADER command in the argument area
    if {[catch {TCL_Write_Int $target(handle) $paramIndexforApplets $appletAddrArgv0} dummy_err] } {
        error "Error Writing Applet pmeccParam Type \n$dummy_err"
    }
    # Write the paramValue for APPLET_CMD_PMECC_HEADER command in the argument area
    if {[catch {TCL_Write_Int $target(handle) $paramValue $appletAddrArgv1} dummy_err] } {
        error "Error Writing Applet pmeccParam Type \n$dummy_err"
    }
    # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $GENERIC::appletCmd(pmeccParam)]} dummy_err]} {
       error "Applet configure pmeccParam type command has not been launched ($dummy_err)"
    }
    if { $result == 0 } {
       puts "-I- Pmecc header configration successful"
       set  curParamHeader [TCL_Read_Int $target(handle) $appletAddrArgv0]
       puts "-I- PMECC configure [format "%x" [expr $curParamHeader & 0xffffffff]]"
       set GENERIC::nandflashCurParam $curParamHeader
       return 1
    } else {
       error "-E- Pmecc header configration failed!"
       return -1
    }
}

#===============================================================================
#  proc NANDFLASH::SendBootFilePmeccCmd
#-------------------------------------------------------------------------------
proc NANDFLASH::SendBootFilePmeccCmd {fileName} { 
    global softwareStatusLabelVariable
    global backupDirPath
    global conWindows
    global target
    variable appletArg
    variable appletCmd
    variable appletAddr
    variable appletMailboxAddr
    variable appletBufferAddress

    if { $GENERIC::nandflashInitialized == 0} {
        puts "-E- Nand flash not initialized!"
        return -1
    }
    if {$fileName == ""} {
        puts "-E- No File Selected"
        return
    }
    if { [catch {set size [file size $fileName]}] } {
        puts "-E- Can't open file $fileName"
        return
    }
    if { $size > $BOARD::maxBootSize } {
        puts "-E- Unauthorized Boot File Size"
        return
    }
    
    if { [catch {set f [open $fileName r]}] } {
        puts "-E- Can't open file $fileName"
        return
    }

    fconfigure $f -translation binary

    set softwareStatusLabelVariable "Sending data ..."
    set dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArgv0     [expr $appletMailboxAddr + 0x08]
    set appletAddrArgv1     [expr $appletMailboxAddr + 0x0c]
    set appletAddrArgv2     [expr $appletMailboxAddr + 0x10]
    set appletAddrArgv3     [expr $appletMailboxAddr + 0x14]

    set maxBufferSize [expr $GENERIC::appletBufferSize]

    # Init the ping pong algorithm: the buffer is active
    set bufferAddress $GENERIC::appletBufferAddress

    # Read Data From Input File
    set rawData [read $f $size]
    
    # Copy in RAM the content of the page to be written
    TCL_Write_Data $target(handle) $bufferAddress rawData $size dummy_err
     
    # If this is a boot file modify 6th vector with file size
    TCL_Write_Int $target(handle) $size [expr $bufferAddress + (5 * 4)] dummy_err

    # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $GENERIC::appletCmd(pmeccBoot) $appletAddrCmd} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }
    # Write the buffer address in the argument area
    if {[catch {TCL_Write_Int $target(handle) $bufferAddress $appletAddrArgv0} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }
    # Write the buffer size in the argument area
    if {[catch {TCL_Write_Int $target(handle) $size $appletAddrArgv1} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }
    # Write the memory offset in the argument area
    if {[catch {TCL_Write_Int $target(handle) 0 $appletAddrArgv2} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }

    # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $GENERIC::appletCmd(pmeccBoot)]} dummy_err]} {
        error "[format "0x%08x" $dummy_err]"
    }

    #Close the wait window
    set softwareStatusLabelVariable ""

    # Store the current dir
    set backupDirPath [file dirname $fileName]
    puts "Sending boot file done."
    close $f
    return 1
}

#===============================================================================
#  proc NANDFLASH::SendBootFilePmecc
#-------------------------------------------------------------------------------
proc NANDFLASH::SendBootFilePmecc {} { 
    global softwareStatusLabelVariable
    global backupDirPath
    global conWindows
    global target
    if { $GENERIC::nandflashInitialized == 0} {
        puts "-E- Nand flash not initialized!"
        return -1
    }
    set fileName [tk_getOpenFile -parent $conWindows -initialdir  $backupDirPath -defaultextension ".bin" -filetypes {{"Bin Files" {.bin}} {"All Files" {*.*}}}]
    if {$fileName == ""} {
        puts "-E- No File Selected"
        return
    }
    NANDFLASH::SendBootFilePmeccCmd $fileName
}

#===============================================================================
#  proc NANDFLASH::BadBlockList
#-------------------------------------------------------------------------------
proc NANDFLASH::BadBlockList {} {
    global target
    variable appletMailboxAddr

    set dummy_err 0
    if { $GENERIC::nandflashInitialized == 0} {
        puts "-E- Nand flash not initialized!"
        return -1
    }

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    # Address where applet write bad block number
    set appletAddrArgv0     [expr $appletMailboxAddr + 0x08]
    # Address of the buffer containing bad blocks list
    set appletAddrArgv1     [expr $appletMailboxAddr + 0x0c]
    set appletAddrArgv2     [expr $appletMailboxAddr + 0x10]
    set appletAddrArgv3     [expr $appletMailboxAddr + 0x14]


    # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $GENERIC::appletCmd(listbadblocks) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }

    # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $GENERIC::appletCmd(listbadblocks)]} dummy_err]} {
        error "Applet List Bad Blocks command has not been launched ($dummy_err)"
    }

    # Read the number of Bad Blocks found
    if {[catch {set nbBadBlocks [TCL_Read_Int $target(handle) $appletAddrArgv0]} dummy_err] } {
        error "Error reading the applet result"
    }

    if { $nbBadBlocks == 0 } {
        puts "-I- No Bad Block found"
        return 1
    } else {
        # Read the address the Bad Blocks list
        if {[catch {set badBlocksListAddr [TCL_Read_Int $target(handle) $appletAddrArgv1]} dummy_err] } {
            error "Error reading the applet result"
        }
        
        puts "-I- Found $nbBadBlocks Bad Blocks :"
        while {$nbBadBlocks > 0} {
            if {[catch {set blockId [TCL_Read_Int $target(handle) $badBlocksListAddr]} dummy_err] } {
                error "Error reading the applet result"
            }

            incr nbBadBlocks -1
            incr badBlocksListAddr 4
            puts "\t Block $blockId"
        }
        return 1
    }

    return 1
}

#===============================================================================
#  proc NANDFLASH::TagBlock
#-------------------------------------------------------------------------------
proc NANDFLASH::TagBlock {blockId type} {   
    global target
    variable appletMailboxAddr
    
    set dummy_err 0
    if { $GENERIC::nandflashInitialized == 0} {
        puts "-E- Nand flash not initialized!"
        return -1
    }

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArgv0     [expr $appletMailboxAddr + 0x08]
    set appletAddrArgv1     [expr $appletMailboxAddr + 0x0c]
    set appletAddrArgv2     [expr $appletMailboxAddr + 0x10]
    set appletAddrArgv3     [expr $appletMailboxAddr + 0x14]


    if {$type == "GOOD"} {
        set tag 0xFF
    } else {
        set tag 0x00
    }
    
    # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $GENERIC::appletCmd(tagBlock) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }
    
    # Write the block ID in the argument area
    if {[catch {TCL_Write_Int $target(handle) $blockId $appletAddrArgv0} dummy_err] } {
    error "Error Writing Applet Block ID \n$dummy_err"
    }
    
    # Write the tag in the argument area
    if {[catch {TCL_Write_Int $target(handle) $tag $appletAddrArgv1} dummy_err] } {
    error "Error Writing Applet TAG \n$dummy_err"
    }
    
     # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $GENERIC::appletCmd(tagBlock)]} dummy_err]} {
        error "Applet TagBlock command has not been launched ($dummy_err)"
    }
    
    if { $result == 0 } {
        return 1
    } else  {
        return -1
    }
}

#===============================================================================
#  proc NANDFLASH::EraseAll
#-------------------------------------------------------------------------------
proc NANDFLASH::BatchEraseAll {param } {
    global target
    global softwareStatusLabelVariable
    variable appletMailboxAddr
    if { $GENERIC::nandflashInitialized == 0} {
        puts "-E- Nand flash not initialized!"
        return -1
    }
    set dummy_err 0
    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArgv0     [expr $appletMailboxAddr + 0x08]
    set appletAddrArgv1     [expr $appletMailboxAddr + 0x0c]

    set softwareStatusLabelVariable "Full Erase in progress ..."
    set eraseBatch 0
    set eraseDone 0
    while {$eraseDone == 0} {
        puts "-I- Erasing  blocks  batch [format "%d" $eraseBatch]"
        # Write the Cmd op code in the argument area
        if {[catch {TCL_Write_Int $target(handle) $GENERIC::appletCmd(batchErase) $appletAddrCmd} dummy_err] } {
            set softwareStatusLabelVariable ""
            error "Error Writing Applet command ($dummy_err)"
        }
        # Write the buffer address in the argument area
        if {[catch {TCL_Write_Int $target(handle) $param $appletAddrArgv0} dummy_err] } {
            set softwareStatusLabelVariable ""
            error "Error Writing Applet erase all \n$dummy_err"
        }
        # Write the buffer address in the argument area
        if {[catch {TCL_Write_Int $target(handle) $eraseBatch $appletAddrArgv1} dummy_err] } {
            set softwareStatusLabelVariable ""
            error "Error Writing Applet erase all \n$dummy_err"
        }
       
        # Launch the applet Jumping to the appletAddr
        if {[catch {set result [GENERIC::Run $GENERIC::appletCmd(batchErase)]} dummy_err]} {
            set softwareStatusLabelVariable ""
            error "Applet erase all command has not been launched ($dummy_err)"
        }
        set eraseBatch [TCL_Read_Int $target(handle) $appletAddrArgv0]
        if {$eraseBatch == 0} {
            set eraseDone 1
        }
    }
    set softwareStatusLabelVariable ""
    
}

#===============================================================================
#  proc NANDFLASH::BlockErase
#-------------------------------------------------------------------------------
proc NANDFLASH::EraseBlocks {start end} {   
    global target
    variable appletMailboxAddr
    
    set dummy_err 0
        if { $GENERIC::nandflashInitialized == 0} {
        puts "-E- Nand flash not initialized!"
        return -1
    }
    
  # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArgv0     [expr $appletMailboxAddr + 0x08]
    set appletAddrArgv1     [expr $appletMailboxAddr + 0x0c]
   
    if {$start > $end } {
        puts "-E- invalid address"
        return -1
    }
    if {[regexp {^(0[xX])([0-9a-fA-F]+)$} $start] == 0} {
       set addrStart [format "0x%s" $start]
    } else {
       set addrStart [format "0x%x" $start]
    }
    if {[regexp {^(0[xX])([0-9a-fA-F]+)$} $end] == 0} {
       set addrend [format "0x%s" $end]
    } else {
       set addrend [format "0x%x" $end]
    }
    
    puts "-I- Erase blocks from start 0x$start to 0x$end" 
    # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $GENERIC::appletCmd(eraseBlocks) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }
    
    # Write the address offest in the argument area
    if {[catch {TCL_Write_Int $target(handle) $addrStart $appletAddrArgv0} dummy_err] } {
    error "Error Writing Applet Address \n$dummy_err"
    }
    
    # Write the number of blocks in the argument area
    if {[catch {TCL_Write_Int $target(handle) $addrend $appletAddrArgv1} dummy_err] } {
    error "Error Writing Applet Address \n$dummy_err"
    }
    
    # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $GENERIC::appletCmd(eraseBlocks)]} dummy_err]} {
        error "Applet Block Erase command has not been launched ($dummy_err)"
    }
    if { $result == 0 } {  
        puts "-I- Blocks from address 0x$start to  0x$end erased"
        return 1
    } else  {
        puts "-E- Erase failed"
        return -1
    }  
}


################################################################################
## NAMESPACE NORFLASH
################################################################################
namespace eval NORFLASH {
    # Following variables are defined in <board>.tcl
    variable appletAddr
    variable appletMailboxAddr
    variable appletFileName
}

#===============================================================================
#  proc NORFLASH::Init
#-------------------------------------------------------------------------------
proc NORFLASH::Init {} {
    global target
    variable appletAddr
    variable appletMailboxAddr
    variable appletFileName
    
    puts "-I- NORFLASH::Init (trace level : $target(traceLevel))"
    
    # Load the applet to the target
    GENERIC::Init $NORFLASH::appletAddr $NORFLASH::appletMailboxAddr $NORFLASH::appletFileName [list $target(comType) $target(traceLevel)]
}

#===============================================================================
#  proc NORFLASH::EraseAll
#-------------------------------------------------------------------------------
proc NORFLASH::EraseAll {} {
    global target
    global softwareStatusLabelVariable
    variable appletMailboxAddr
    
    set dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArgv0     [expr $appletMailboxAddr + 0x08]
    set appletAddrArgv1     [expr $appletMailboxAddr + 0x0c]
    set appletAddrArgv2     [expr $appletMailboxAddr + 0x10]
    set appletAddrArgv3     [expr $appletMailboxAddr + 0x14]

    set softwareStatusLabelVariable "Full Erase in progress ..."
    
    set sizeToErase $GENERIC::memorySize
    set eraseOffset 0
    
    # Save the size of memory to be erased
    set fileSize $sizeToErase
    
    while {$sizeToErase > 0} {
        # Update Status Lable
        GENERIC::UpdateStatusLabel $sizeToErase $fileSize

        puts "-I- \tErasing  blocks at address [format "0x%X" $eraseOffset]"
        # Write the Cmd op code in the argument area
        if {[catch {TCL_Write_Int $target(handle) $GENERIC::appletCmd(erasebuffer) $appletAddrCmd} dummy_err] } {
            set softwareStatusLabelVariable ""
            error "Error Writing Applet command ($dummy_err)"
        }
        # Write the buffer address in the argument area
        if {[catch {TCL_Write_Int $target(handle) $eraseOffset $appletAddrArgv0} dummy_err] } {
            set softwareStatusLabelVariable ""
            error "Error Writing Applet erase all \n$dummy_err"
        }
        # Launch the applet Jumping to the appletAddr
        if {[catch {set result [GENERIC::Run $GENERIC::appletCmd(erasebuffer)]} dummy_err]} {
            set softwareStatusLabelVariable ""
            error "Applet erase all command has not been launched ($dummy_err)"
        }
        set bytesErased [TCL_Read_Int $target(handle) $appletAddrArgv0]
        incr eraseOffset $bytesErased
        set sizeToErase  [expr $sizeToErase - $bytesErased]
    }
    set softwareStatusLabelVariable ""
    
}


################################################################################
## NAMESPACE FLASH
################################################################################
namespace eval FLASH {
    # Following variables are defined in <board>.tcl
    variable appletAddr
    variable appletMailboxAddr
    variable appletFileName
    variable flashSize
    variable flashLockRegionSize
    variable flashNumbersLockBits
    variable ForceUnlockBeforeWrite 0
    variable ForceLockAfterWrite 0
}

#===============================================================================
#  proc FLASH::Init
#-------------------------------------------------------------------------------
proc FLASH::Init { {bank 0} } {
    global target
    variable appletAddr
    variable appletMailboxAddr
    variable appletFileName

    # bank parameter is used for SAM3 devices where two flash memories are at two different base addresses
    GENERIC::Init $FLASH::appletAddr $FLASH::appletMailboxAddr $FLASH::appletFileName [list $target(comType) $target(traceLevel) $bank]
}

#===============================================================================
#  proc FLASH::AskForLockSector
#-------------------------------------------------------------------------------
proc FLASH::AskForLockSector { first_lockregion last_lockregion } {
    global   target
    global   commandLineMode
    variable appletMailboxAddr
    variable ForceLockAfterWrite
    
    set dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArgv0     [expr $appletMailboxAddr + 0x08]
    set appletAddrArgv1     [expr $appletMailboxAddr + 0x0c]
    set appletAddrArgv2     [expr $appletMailboxAddr + 0x10]
    set appletAddrArgv3     [expr $appletMailboxAddr + 0x14]
    set ForceLockAfterWrite 0
    if {$commandLineMode == 0} {
        # Ask for Lock Sector(s)
        set answer [tk_messageBox -title "Lock region(s)"\
        -message " Do you want to lock involved lock region(s) ($first_lockregion to $last_lockregion) ? "\
        -icon question -type yesno \
        -detail "\"Yes\" Lock it"]
        switch -- $answer {
           yes { set ForceLockAfterWrite 1 }
           no  { puts "Do not lock " }
        }
    }
    if {$ForceLockAfterWrite} {
        # Lock all sectors involved in the write
        for {set i $first_lockregion} {$i <= $last_lockregion } {incr i} {
            # Write the Cmd op code in the argument area
            if {[catch {TCL_Write_Int $target(handle) $GENERIC::appletCmd(lock) $appletAddrCmd} dummy_err] } {
                error "Error Writing Applet command ($dummy_err)"
            }   
            # Write the page number in the argument area
            if {[catch {TCL_Write_Int $target(handle) $i $appletAddrArgv0} dummy_err] } {
                error "Error Writing Applet page \n$dummy_err"
            }
            # Launch the applet Jumping to the appletAddr
            if {[catch {set result [GENERIC::Run $GENERIC::appletCmd(lock)]} dummy_err]} {
                error "Applet unlock command has not been launched ($dummy_err)"
            }
            puts "-I- Sector $i locked"
        }
    }

    return 1
}

#===============================================================================
#  proc FLASH::AskForUnlockSector
#-------------------------------------------------------------------------------
proc FLASH::AskForUnlockSector { first_lockregion last_lockregion } {  
    global target
    global commandLineMode
    variable appletMailboxAddr
    variable ForceUnlockBeforeWrite
        
    set dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArgv0     [expr $appletMailboxAddr + 0x08]
    set appletAddrArgv1     [expr $appletMailboxAddr + 0x0c]
    set appletAddrArgv2     [expr $appletMailboxAddr + 0x10]
    set appletAddrArgv3     [expr $appletMailboxAddr + 0x14]

    set ForceUnlockBeforeWrite 0
    # Ask for Unlock Sector(s)
    if {$commandLineMode == 0} {
        set answer [tk_messageBox -title "Unlock region(s)"\
        -message " Do you want to unlock involved lock region(s) ($first_lockregion to $last_lockregion) ? "\
        -icon question -type yesno \
        -detail "\"Yes\" unlock it"]
        switch -- $answer {
           yes { set ForceUnlockBeforeWrite 1 }
           no  { puts "Do not unlock " }
        }
    }
    if {$ForceUnlockBeforeWrite} {
        # Unlock all sectors involved in the write    
        for {set i $first_lockregion} {$i <= $last_lockregion } {incr i} {
            # Write the Cmd op code in the argument area
            if {[catch {TCL_Write_Int $target(handle) $GENERIC::appletCmd(unlock) $appletAddrCmd} dummy_err] } {
                error "Error Writing Applet command ($dummy_err)"
            }   
        
            # Write the page number in the argument area
            if {[catch {TCL_Write_Int $target(handle) $i $appletAddrArgv0} dummy_err] } {
                error "Error Writing Applet page \n$dummy_err"
            }
            # Launch the applet Jumping to the appletAddr
            if {[catch {set result [GENERIC::Run $GENERIC::appletCmd(unlock)]} dummy_err]} {
                error "Applet unlock command has not been launched ($dummy_err)"
            }
            puts "-I- Sector $i unlocked"
        }
    }

    return 1
}

#===============================================================================
#  proc FLASH::SendFile
#-------------------------------------------------------------------------------
proc FLASH::SendFile { name addr } {
    variable flashSize  
    variable flashLockRegionSize   
    variable flashNumbersLockBits 
    variable appletBufferAddress

    if { [catch {set f [open $name r]}] } {
        puts "-E- Can't open file $name"
        return -1
    }
    fconfigure $f -translation binary
    
    #First Step check the locked sector 
    set dummy_err 0
    set rewrite 0
    set size [file size $name]
    
    set dest [expr $addr & [expr  $flashSize - 1]]    

    # Compute first and last lock regions
    #set lockRegionSize [expr $flashSize / $flashNumbersLockBits]
    set first_sector [expr $dest / $FLASH::flashLockRegionSize]
    set last_sector [expr [expr [expr $dest + $size] -1 ] / $FLASH::flashLockRegionSize]
    puts " first_sector $first_sector last_sector $last_sector "
    
    if {[catch {GENERIC::Write $dest $size $f 0} dummy_err] } {
        switch $dummy_err {
            0x00000004 {
                # Check for locked lock regions in order to unlock them, return if user refuses
                set returnValue [FLASH::AskForUnlockSector $first_sector $last_sector]
                if {$returnValue == -1} {
                    puts "-E- FLASH::SendFile failed: some lock regions are always locked !"
                    close $f
                    return -1
                } else {set rewrite 1}
            }
            default  {
                puts "-E- Generic::Write returned error ($dummy_err)"
                close $f
                return -1
            }
       }
    }
    if {$rewrite == 1} {
        seek $f 0 start
        if {[catch {GENERIC::Write $dest $size $f 0} dummy_err] } {
            puts "-E- Generic::Write returned error ($dummy_err)"
            close $f
            return -1
        }
    }
    # Lock all sectors involved in the write
    FLASH::AskForLockSector $first_sector $last_sector
    close $f
}

#===============================================================================
#  proc FLASH::receiveFile
#-------------------------------------------------------------------------------
proc FLASH::ReceiveFile { name addr size } {

    variable flashSize  
    set dummy_err 0
    
    set dest [expr $addr & [expr  $flashSize -1 ]]
    if {[catch {GENERIC::ReceiveFile $name $dest $size} dummy_err] } {
        puts "-E- Generic:: receiveFile returned error ($dummy_err)"
    }
}

#===============================================================================
#  proc FLASH::EraseAll
#-------------------------------------------------------------------------------
proc FLASH::EraseAll { } {
    variable flashNumbersLockBits   
    global softwareStatusLabelVariable
    set dummy_err 0
    set reerase 0

    global softwareStatusLabelVariable
    set softwareStatusLabelVariable "Full Erase in progress ..."
    
    if {[catch {GENERIC::EraseAll} dummy_err] } {
        switch $dummy_err {
            0x00000004 {
                # Check for locked lock regions in order to unlock them, return if user refuses
                set returnValue [FLASH::AskForUnlockSector 0 [expr $flashNumbersLockBits -1]]
                if {$returnValue == -1} {
                    set softwareStatusLabelVariable ""
                    puts "-E- Send file failed: some lock regions are always locked !"
                    return -1
                } else {set reerase 1}
            }
            default  {
                puts "-E- Generic::EraseAll returned error ($dummy_err)"
                set softwareStatusLabelVariable ""
                return -1
            }
       }
    }
    if {$reerase == 1} {
        if {[catch {GENERIC::EraseAll} dummy_err] } {
            set softwareStatusLabelVariable ""
            puts "-E- Generic::EraseAll returned error ($dummy_err)"
            return -1
        }
    }
   
    set softwareStatusLabelVariable ""
    return 1
}


#===============================================================================
#  proc FLASH::ScriptGPNMV
#-------------------------------------------------------------------------------
proc FLASH::ScriptGPNMV {index} {   
    global   target
    variable appletMailboxAddr
        
    set dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArgv0     [expr $appletMailboxAddr + 0x08]
    set appletAddrArgv1     [expr $appletMailboxAddr + 0x0c]
    set appletAddrArgv2     [expr $appletMailboxAddr + 0x10]
    set appletAddrArgv3     [expr $appletMailboxAddr + 0x14]

    # Clear GPNVM : action=0
    # Set GPNVM   : action=1

    switch $index {
        0 {
            set action  1
            set gp 0
        }
        1 {
            set action  0
            set gp 0
        }
        2 {
            set action  1
            set gp 1
        }
        3 {
            set action  0
            set gp 1
        }
        4 {
            set action  1
            set gp 2
        }
        5 {
            set action  0
            set gp 2
        }
        6 {
            set action  1
            set gp 3
        }
        7 {
            set action  0
            set gp 3
        }        
    }
    
    # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $GENERIC::appletCmd(gpnvm) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }
    
    # Write the gpnvm action in the argument area
    if {[catch {TCL_Write_Int $target(handle) $action $appletAddrArgv0} dummy_err] } {
    error "Error Writing Applet GPNVM action \n$dummy_err"
    }
    
    # Write the gpnvm bit of nvm in the argument area
    if {[catch {TCL_Write_Int $target(handle) $gp $appletAddrArgv1} dummy_err] } {
    error "Error Writing Applet GPNVM index \n$dummy_err"
    }
    
     # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $GENERIC::appletCmd(gpnvm)]} dummy_err]} {
        error "Applet GPNVM command has not been launched ($dummy_err)"
    }
    
    if { $action == 1 } {
        if { $result != 0 } {
            puts "-E- Set GPNVM$gp failed"
            return -1
        } else  {puts "-I- GPNVM$gp set"}
    } else {
        if { $result != 0 } {
            puts "-E- Clear GPNVM$gp failed"
            return -1
        } else  {puts "-I- GPNVM$gp cleared"}
    }

    return 1
}

#===============================================================================
#  proc FLASH::ScriptSetSecurityBit
#-------------------------------------------------------------------------------
proc FLASH::ScriptSetSecurityBit { } {
    global   target
    variable appletMailboxAddr
    set      dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArgv0     [expr $appletMailboxAddr + 0x08]
    set appletAddrArgv1     [expr $appletMailboxAddr + 0x0c]
    set appletAddrArgv2     [expr $appletMailboxAddr + 0x10]
    set appletAddrArgv3     [expr $appletMailboxAddr + 0x14]

    # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $GENERIC::appletCmd(security) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }
    
    # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $GENERIC::appletCmd(security)]} dummy_err]} {
        error "Applet set security command has not been launched ($dummy_err)"
    }
    puts "-I- Security Bit Set"
}

#===============================================================================
#  proc FLASH::ReadUniqueID
#-------------------------------------------------------------------------------
proc FLASH::ReadUniqueID { } {
    global   target
    variable appletMailboxAddr
    set      dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArgv0     [expr $appletMailboxAddr + 0x08]
    set appletAddrArgv1     [expr $appletMailboxAddr + 0x0c]
    set appletAddrArgv2     [expr $appletMailboxAddr + 0x10]
    set appletAddrArgv3     [expr $appletMailboxAddr + 0x14]

    # Init the ping pong algorithm: the buffer is active
    set bufferAddress $GENERIC::appletBufferAddress

    # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $GENERIC::appletCmd(readUniqueID) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }
    
    # Write the buffer address in the argument area
    if {[catch {TCL_Write_Int $target(handle) $bufferAddress $appletAddrArgv0} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }

    # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $GENERIC::appletCmd(readUniqueID)]} dummy_err]} {
        error "Applet set security command has not been launched ($dummy_err)"
    }

    puts "buffer address [format "0x%08x" $bufferAddress]"

    puts "Unique ID :"

    # Read the page containing the unique ID
    set i 0
    while {$i < [expr 256 / 4]} {
        set addr [expr $bufferAddress + $i * 4]
        # Return the error code returned by the applet
        if {[catch {set data [TCL_Read_Int $target(handle) $addr]} dummy_err] } {
            error "Error reading the buffer containing Unique ID"
        }

        puts [format "\t0x%04x : 0x%08x" [expr $i * 4] $data]
        incr i +1
    }
}

################################################################################
## NAMESPACE SDMMC
################################################################################
namespace eval SDMMC {
    # Following variables are defined in <board>.tcl
    variable appletAddr
    variable appletMailboxAddr
    variable appletFileName
}

#===============================================================================
#  proc SDMMC::Init
#-------------------------------------------------------------------------------
proc SDMMC::Init {} {
    global target
    variable appletAddr
    variable appletMailboxAddr
    variable appletFileName
    
    puts "-I- SDMMC::Init (trace level : $target(traceLevel))"
    
    # Load the applet to the target
    GENERIC::Init $SDMMC::appletAddr $SDMMC::appletMailboxAddr $SDMMC::appletFileName [list $target(comType) $target(traceLevel)]
}
################################################################################
## NAMESPACE OTP
################################################################################
namespace eval OTP {
    # Following variables are defined in <board>.tcl
    variable appletAddr
    variable appletMailboxAddr
    variable appletFileName
}

#===============================================================================
#  proc OTP::Init
#-------------------------------------------------------------------------------
proc OTP::Init {} {
    global target
    global commandLineMode
    global   otpStatus 
    variable appletAddr
    variable appletMailboxAddr
    variable appletFileName
    if {$commandLineMode == 0} {
        puts "-I- OTP::Init (trace level : $target(traceLevel))"
        # Load the applet to the target
        GENERIC::Init $OTP::appletAddr $OTP::appletMailboxAddr $OTP::appletFileName [list $target(comType) $target(traceLevel)]
        set otpStatus {}
        OTP::Read
    } else {
        puts "Does not support command line mode for OTP fuse!"
    }
}

#===============================================================================
#  proc OTP::Read
#-------------------------------------------------------------------------------
proc OTP::Read { } {
    global   target
    global   otpStatus
    
    variable appletMailboxAddr
    variable isCfg
    set      dummy_err 0
    set otpStatus {}

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArgv0     [expr $appletMailboxAddr + 0x08]
    set appletAddrArgv1     [expr $appletMailboxAddr + 0x0c]
    set appletAddrArgv2     [expr $appletMailboxAddr + 0x10]
    set appletAddrArgv3     [expr $appletMailboxAddr + 0x14]
    set isCfg 0

    for {set i 0} {$i < $OTP::otpSizeinWord } {incr i} {
        # Write the Cmd op code in the argument area
        if {[catch {TCL_Write_Int $target(handle) $GENERIC::appletCmd(otpRead) $appletAddrCmd} dummy_err] } {
            error "Error Writing Applet command ($dummy_err)"
        }
        # Write the word address in the argument area
        if {[catch {TCL_Write_Int $target(handle) $i $appletAddrArgv0} dummy_err] } {
            error "[format "0x%08x" $dummy_err]"
        }
        if {$i == $OTP::otpSizeinWord} {
            set isCfg 1
        }
        # Write the cfg flag in the argument area
        if {[catch {TCL_Write_Int $target(handle) $isCfg $appletAddrArgv1} dummy_err] } {
            error "[format "0x%08x" $dummy_err]"
        }
        # Launch the applet Jumping to the appletAddr
        if {[catch {set result [GENERIC::Run $GENERIC::appletCmd(otpRead)]} dummy_err]} {
            error "Applet read OTP command has not been launched ($dummy_err)"
        }
        # Return the error code returned by the applet
        if {[catch {set data [TCL_Read_Int $target(handle) $appletAddrArgv0]} dummy_err] } {
            error "Error reading the OTP data"
        }
        if {$isCfg == 1} {
            set startOtpAddr  [expr $i * 32]
            set endOtpAddr  [expr [expr [expr $i + 1] * 32] - 1]
            puts "\[$endOtpAddr:$startOtpAddr\] [format "0x%08x" $data]"
        } else {
            set startOtpAddr  [expr $i * 32]
            set endOtpAddr  [expr [expr [expr $i + 1] * 32] - 1]
            puts "\[$endOtpAddr:$startOtpAddr\] [format "0x%08x" $data]"
        }
        lappend otpStatus $data
        
    }
}

#===============================================================================
#  proc OTP::FuseIF
#-------------------------------------------------------------------------------
proc OTP::FuseIF { wordSize cfglist} {
    global otpStatus 
    global otpFuse

    set returnValue [otpdlg $wordSize $cfglist]
    if { $returnValue == 1 } {
        #puts "otpFuse $otpFuse(data) wordAddr $otpFuse(word)"
        # for CGF AREA
        if { $otpFuse(word) == [expr $wordSize -1 ]} {
            set startAddr [format "%03d" [expr [expr $otpFuse(word) *32] - 24 ] ]
        } else {
            set startAddr [format "%03d" [expr $otpFuse(word) *32]]
        }
        set endAddr [format "%03d" [expr [expr [expr $otpFuse(word) + 1] * 32] - 1 ] ]
        
        set dumpAddr "\[$endAddr : $startAddr\]" 
        
        set answer [tk_messageBox -title "OTP Fuse"\
        -message "The OTP bits in $dumpAddr will be programmed $otpFuse(data) \n\r \
        When the OTP bit is set '1', it cannot be set to '0' again, \n\r \
        Do you want to fuse it?" -icon question -type yesno \
        -detail "Select \"Yes\" Fuse OTP"]
        switch -- $answer {
           yes { OTP::Write $otpFuse(word) $otpFuse(data) }
           no { puts "fuse cancelled" }
        }
    }
}

#===============================================================================
#  proc OTP::Write
#-------------------------------------------------------------------------------
proc OTP::Write { wordAddr data } {
    global   target
    variable appletMailboxAddr
    variable isCfg
    set      dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArgv0     [expr $appletMailboxAddr + 0x08]
    set appletAddrArgv1     [expr $appletMailboxAddr + 0x0c]
    set appletAddrArgv2     [expr $appletMailboxAddr + 0x10]
    set appletAddrArgv3     [expr $appletMailboxAddr + 0x14]
    set isCfg 0
    if {$wordAddr >= $OTP::otpSizeinWord} {
        error "Error Word Address for OTP write command ($dummy_err)"
    }

    # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $GENERIC::appletCmd(otpWrite) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }
    # Write the word address in the argument area
    if {[catch {TCL_Write_Int $target(handle) $wordAddr $appletAddrArgv0} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }
    if {$wordAddr == [expr $OTP::otpSizeinWord - 1]} {
        set isCfg 1
        puts "Write CFG"
    }
    # Write the cfg flag in the argument area
    if {[catch {TCL_Write_Int $target(handle) $isCfg $appletAddrArgv1} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }
    # Write the data in the argument area
    if {[catch {TCL_Write_Int $target(handle) $data $appletAddrArgv2} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }

    # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $GENERIC::appletCmd(otpWrite)]} dummy_err]} {
        error "Applet Write OTP command has not been launched ($dummy_err)"
    }
}

#===============================================================================
#  proc SDMMC::Init
#===============================================================================

proc SDMMC::Init {} {
    global target
    puts "-I- Load messStorage binary"
    # Load the applet to the target
    if {[catch {GENERIC::LoadApplet $SDMMC::appletAddr $SDMMC::appletFileName} dummy_err]} {
        error "Applet $appletFileName can not be loaded"
    }
    if {[catch {TCL_Go $target(handle) $SDMMC::appletAddr} dummy_err] } {
        error "Error Running the applet"
    }
    TCL_Close $target(handle)
    exit
}
