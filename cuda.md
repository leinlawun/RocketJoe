#Driver and Cuda Toolkit 

## ubuntu 19.04

### Remove

    sudo rm /etc/apt/sources.list.d/cuda*
    sudo apt remove --autoremove nvidia-cuda-toolkit
    sudo apt remove --autoremove nvidia-*
    sudo apt remove --purge nvidia* && sudo apt autoremove
    sudo rm -r /var/lib/dkms/nvidia
    sudo apt install --reinstall dkms
    sudo apt purge 'nvidia.*'

### Pre Install 

    sudo touch /etc/modprobe.d/blacklist-nouveau.conf
    
add sudo vim /etc/modprobe.d/blacklist-nouveau.conf
    
    blacklist nouveau
    options nouveau modeset=0
exit 
        
    sudo update-initramfs -u
    sudo reboot    

### Install Driver
    
    sudo add-apt-repository ppa:graphics-drivers/ppa
    sudo apt install build-essential
    sudo apt install nvidia-driver-430
    sudo reboot
    prime-select intel
    sudo reboot
    
add sudo vim /lib/modprobe.d/blacklist-nvidia.conf 
    
    # Do not modify
    # This file was generated by nvidia-prime
    #blacklist nvidia
    blacklist nvidia-drm
    #blacklist nvidia-modeset
    #alias nvidia off
    alias nvidia-drm off
    #alias nvidia-modeset off

exit 
    
    sudo reboot
    
### Check   

dkms status    
    
    nvidia, 430.40, 5.0.0-23-generic, x86_64: installed  

cat /lib/modprobe.d/nvidia-graphics-drivers.conf  
    
    blacklist nouveau
    blacklist lbm-nouveau
    alias nouveau off
    alias lbm-nouveau off
  
nvidia-smi    
    
    +-----------------------------------------------------------------------------+
    | NVIDIA-SMI 430.40       Driver Version: 430.40       CUDA Version: 10.1     |
    |-------------------------------+----------------------+----------------------+
    | GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
    | Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
    |===============================+======================+======================|
    |   0  Quadro M2200        Off  | 00000000:01:00.0 Off |                  N/A |
    | N/A   44C    P8    N/A /  N/A |      0MiB /  4043MiB |      0%      Default |
    +-------------------------------+----------------------+----------------------+
                                                                                   
    +-----------------------------------------------------------------------------+
    | Processes:                                                       GPU Memory |
    |  GPU       PID   Type   Process name                             Usage      |
    |=============================================================================|
    |  No running processes found                                                 |
    +-----------------------------------------------------------------------------+

### Install Cuda toolkit

    sudo apt-key adv --fetch-keys  http://developer.download.nvidia.com/compute/cuda/repos/ubuntu1810/x86_64/7fa2af80.pub
    sudo bash -c 'echo "deb http://developer.download.nvidia.com/compute/cuda/repos/ubuntu1810/x86_64 /" > /etc/apt/sources.list.d/cuda.list'
    sudo apt update
    sudo apt install cuda-10-1

    
add vim ~/.profile    

    if [ -d "/usr/local/cuda-10.1/bin/" ]; then
        export PATH=/usr/local/cuda/bin${PATH:+:${PATH}}
        export LD_LIBRARY_PATH=/usr/local/cuda/lib64${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
    fi
    
exit     

### Check 

nvcc --version

    nvcc: NVIDIA (R) Cuda compiler driver
    Copyright (c) 2005-2019 NVIDIA Corporation
    Built on Wed_Apr_24_19:10:27_PDT_2019
    Cuda compilation tools, release 10.1, V10.1.168

    
###URL HELP 

    https://linuxconfig.org/how-to-disable-nouveau-nvidia-driver-on-ubuntu-18-04-bionic-beaver-linux
    https://askubuntu.com/questions/251754/why-would-modinfo-say-a-module-is-not-found-when-it-appears-with-lsmod
    https://askubuntu.com/questions/1122512/nvidia-modules-are-missing-after-each-kernel-upgrade-in-18-04
    https://wiki.ubuntu.com/UEFI/SecureBoot/DKMS   