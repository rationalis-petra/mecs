with import <nixpkgs> {};
stdenv.mkDerivation {
  name = "mecs";
  nativeBuildInputs = [
    coreutils
    cmake
    glfw3
    libGL
  ];
  buildInputs = [
    xorg.libX11
    xorg.libXrandr
    xorg.libXi
  ];
}
