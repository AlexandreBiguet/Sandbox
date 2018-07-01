I was asking myself about ignoring or not the cargo.lock file:
Short answer : don't ignore it for bins. can be ignores for libs

### Why do binaries have Cargo.lock in version control, but not libraries?

The purpose of a Cargo.lock is to describe the state of the world at the time of
a successful build. It is then used to provide deterministic builds across
whatever machine is building the project by ensuring that the exact same
dependencies are being compiled.

This property is most desirable from applications and projects which are at the
very end of the dependency chain (binaries). As a result, it is recommended that
all binaries check in their Cargo.lock.

For libraries the situation is somewhat different. A library is not only used by
the library developers, but also any downstream consumers of the library. Users
dependent on the library will not inspect the library’s Cargo.lock (even if it
exists). This is precisely because a library should not be deterministically
recompiled for all users of the library.

If a library ends up being used transitively by several dependencies, it’s
likely that just a single copy of the library is desired (based on semver
compatibility). If all libraries were to check in their Cargo.lock, then
multiple copies of the library would be used, and perhaps even a version
conflict.

In other words, libraries specify semver requirements for their dependencies but
cannot see the full picture. Only end products like binaries have a full picture
to decide what versions of dependencies should be used. 
