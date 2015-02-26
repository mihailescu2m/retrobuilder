
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

patch () {
    cd $folder
    echo -e "${BRed}Patching default build options... ${Color_Off}"
    awk 'NR==30{print ""
                print "set(MIPS OFF)"
                print "set(X86 OFF)"
                print "set(ARM ON)"
                print "set(ARMV7 ON)"
                print "set(USING_EGL ON)"
                print "set(USING_FBDEV ON)"
                print "set(USING_GLES2 ON)"
                print "set(USING_QT_UI OFF)"
                print "set(MOBILE_DEVICE ON)"
                print "set(HEADLESS OFF)"
                print "set(UNITTEST OFF)"
                print "set(SIMULATOR OFF)"
                print "set (CMAKE_C_FLAGS \"${CMAKE_C_FLAGS} -march=armv7-a -mfpu=neon\")"
                print "set (CMAKE_CXX_FLAGS \"${CMAKE_CXX_FLAGS} -march=armv7-a -mfpu=neon\")"}1' CMakeLists.txt > CMakeListsPatched.txt
    cp CMakeListsPatched.txt CMakeLists.txt
    rm -rf CMakeListsPatched.txt
    git commit -a -m "Applied patches for $hardware"

    cd "$folder/ffmpeg"
    echo -e "${BRed}Patching ffmpeg... ${Color_Off}"
    sed -i '/{GENERAL}/d' linux_arm.sh
    sed -i '/^build_ARMv6/d' linux_arm.sh
    sed -i 's/softfp/hard/g' linux_arm.sh
    sed -i 's/make install/make install -j3/g' linux_arm.sh
    git commit -a -m "Applied patches for $hardware"

    return 0
}

fetch () {
    echo -e "${Yellow}Fetching $folder... ${Color_Off}"
    mkdir -p "$folder"
    if [[ -d "$folder/.git" ]]; then
        cd $folder
        git pull --progress --rebase
        git submodule update --rebase
    else
        git clone --progress https://github.com/hrydgard/ppsspp $folder
        cd $folder
        git submodule update --progress --init
        patch
    fi
    return 0
}

build () {
    echo -e "${Green}Building $folder... ${Color_Off}"
    cd $folder
    cmake .
    cd $folder/ffmpeg
    ./linux_arm.sh
    cd $folder
    cmake .
    make -j3
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

