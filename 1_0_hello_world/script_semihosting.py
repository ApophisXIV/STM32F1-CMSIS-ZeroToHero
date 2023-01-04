Import("env")

# Semihosting
env.Append(
    LINKFLAGS=["--specs=rdimon.specs -lc -lrdimon"],
    LIBS=["rdimon"]
)
