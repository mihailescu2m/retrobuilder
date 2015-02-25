
module_deps () {
    case $os in
        ubuntu) ;&
        debian)
echo "zlib1g-dev"
            ;;
        *) echo ""
            ;;
    esac
}

fetch () {
    echo -e "${Yellow}Fetching $folder... ${Color_Off}"
    mkdir -p "$folder"
    if [[ -d "$folder/.git" ]]; then
        cd $folder
        git pull --progress --rebase
    else
        git clone --progress https://github.com/libretro/RetroArch $folder 
        patch
    fi
    return 0
}

build () {
    echo -e "${Green}Building $folder... ${Color_Off}"
    cd $folder
    ./configure --disable-x11 --disable-oss --disable-pulse --enable-floathard --enable-mali_fbdev --enable-gles --enable-neon
    make clean
    make -j3 CC="gcc -mfloat-abi=hard -mfpu=neon -mcpu=cortex-a5 -mtune=cortex-a5"
    return 0
}

configure () {
    echo -e "${Cyan}Configuring ${ICyan}$folder${Cyan}... ${Color_Off}"
    return 0
}

