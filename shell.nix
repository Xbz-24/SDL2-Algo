{ pkgs ? import <nixpkgs> {} }:

let
  unstable = import (builtins.fetchTarball "https://github.com/NixOS/nixpkgs/archive/nixos-unstable.tar.gz") {};
in

pkgs.mkShell {
  buildInputs = [
      pkgs.SDL2
      pkgs.SDL2_ttf
      pkgs.pkg-config
      pkgs.boost
      pkgs.cmake
      unstable.fmt
  ];
}
