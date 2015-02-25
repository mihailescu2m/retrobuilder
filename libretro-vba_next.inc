
module_deps () {
    case $os in
        ubuntu) ;&
        debian)
echo ""
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
        git clone --progress https://github.com/libretro/vba-next $folder 
        patch
    fi
    return 0
}

build () {
    echo -e "${Green}Building $folder... ${Color_Off}"
    cd $folder
    make -f Makefile.libretro clean
    make -j3 -f Makefile.libretro platform=armv,neon,hardfloat TILED_RENDERING=1 HAVE_NEON=1
    return 0
}

configure () {
    echo -e "${Cyan}Configuring ${ICyan}$folder${Cyan}... ${Color_Off}"
    return 0
}

