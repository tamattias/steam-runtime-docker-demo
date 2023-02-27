# Steam Runtime Docker Demo

This repository demonstrates setting up GitHub Actions to automatically build
your game (or any other project) for Steam Runtime. It creates a Docker image
capable of building your project with C++17 support. Then, whenever someone
pushes a new commit to the master branch, GitHub will automatically build your
project and upload the built artifact. The built artifact can then be
downloaded from GitHub Actions.
