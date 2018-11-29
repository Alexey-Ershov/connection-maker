{ stdenv, fetchFromGitHub, autoconf, automake, libtool, pkgconfig, openssl, libevent }:

stdenv.mkDerivation rec {
  name = "libfluid_base";

  src = fetchFromGitHub {
    owner = "ARCCN";
    repo = "libfluid_base";
    rev = "4665e673b04c5ec59cee5133192c1c2e098f92d5";
    sha256 = "0fdxm7pspg10v1qk9dqqycr6273wgja7k2f4912fywvafwl7p946";
  };

  nativeBuildInputs = [ autoconf automake libtool pkgconfig ];
  buildInputs = [ openssl ];
  propagatedBuildInputs = [ libevent ];
  CXXFLAGS = ["-std=c++11"];

  preConfigure = ''
    ./autogen.sh
  '';

  enableParallelBuilding = true;
}
