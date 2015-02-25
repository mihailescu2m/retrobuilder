
module_deps () {
    case $os in
        ubuntu) ;&
        debian)
echo "libpng12-dev libfreetype6-dev libboost-filesystem-dev"
            ;;
        *) echo ""
            ;;
    esac
}

patch () {
    cd $folder/$1
    case $1 in
        mupen64plus-video-rice)
            echo -e "${BRed}Patching rice plugin to not use desktop OpenGL$... ${Color_Off}"
            sed -i '/OGLExtensions.cpp/d' projects/unix/Makefile

            git commit -a -m "Applied patches for $hardware"
            ;;
        *)  ;;
    esac
    cd $folder
    return 0
}

fetch () {
    local components="core rom ui-console audio-sdl input-sdl rsp-hle video-rice video-glide64mk2"
    mkdir -p $folder
    cd $folder
    for c in $components; do
        echo -e "${Yellow}Fetching $folder... ${IYellow}$c module ${Color_Off}"
        if [[ -d "mupen64plus-$c/.git" ]]; then
            cd mupen64plus-$c
            git pull --progress --rebase
            cd ..
        else
            git clone --progress https://github.com/mupen64plus/mupen64plus-$c mupen64plus-$c
            patch mupen64plus-$c
        fi
    done
    return 0
}

build () {
    local components="core rom ui-console audio-sdl input-sdl rsp-hle video-rice video-glide64mk2"
    local flags="USE_GLES=1 NEON=1 VFP_HARD=1 OPTFLAGS=-O3 PIC=1 NO_SSE=1 USE_FRAMESKIPPER=1"
    cd $folder
    rm -rf build; mkdir -p build
    for c in $components; do
        echo -e "${Green}Building $folder... ${IGreen}$c module ${Color_Off}"
        if  [ "$c" = "rom" ]; then
            cp mupen64plus-rom/m64p_test_rom.v64 build/
            continue
        fi

        make -C mupen64plus-$c/projects/unix clean $flags
        make -C mupen64plus-$c/projects/unix all $flags -j3
        make -C mupen64plus-$c/projects/unix install $flags -j3 PLUGINDIR= SHAREDIR= BINDIR= MANDIR= LIBDIR= APPSDIR= ICONSDIR=icons INCDIR=api LDCONFIG=true DESTDIR="$folder/build/"

        mkdir -p build/doc
        for doc in LICENSES README RELEASE; do
            if [ -e "mupen64plus-$c/$doc" ]; then
                cp "mupen64plus-$c/$doc" "build/doc/$doc-mupen64plus-$c"
            fi
        done
        for subdoc in gpl-license font-license lgpl-license module-api-versions.txt; do
            if [ -e "mupen64plus/$c/doc/$subdoc" ]; then
                cp "mupen64plus-$c/doc/$subdoc" build/doc/
            fi
        done
    done
    return 0
}

install () {
    echo -e "${Purple}Installing ${IPurple}$folder${Purple}... ${Color_Off}"
    return 0
}

uninstall () {
    echo -e "${Purple}Uninstalling ${IPurple}$folder${Purple}... ${Color_Off}"
    return 0
}

configure () {
    echo -e "${Cyan}Configuring ${ICyan}$folder${Cyan}... ${Color_Off}"
    return 0
}

