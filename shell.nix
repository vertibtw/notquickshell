{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    gcc
    cmake
    just
    pkg-config
    gtkmm4
    gtk4-layer-shell
  ];
}
