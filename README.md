# Kwic

Kwic is a tool that stops you forgetting you auth keys, API keys, or any long strings of text you may need. Instead of rooting through files to find them, just save it in an entry under an alias, and copy it to your clipboard with one short command.<br>


> **Important:** if you don't want to read the whole thing, please just take a look at [this](#disclaimer) and especially **[this.](#dependencies)** For **copyright info** view the [license.](LICENSE)

<br>

## How To Use

Kwic was made quite simple. It only has a few commands you need:

- Make a new entry: ```kwic -n entryalias entryvalue```

- Copy a value: ```kwic -c entryalias```

- Rename an alias: ```kwic -r oldalias newalias```

- Print a value: ```kwic -p entryalias```

    This probably doesn't seem like a very useful one, so here's an example use:

    ```kwic -n pth /home/<home>/path/to/my/project```

    ```cd $(kwic -p pth)``` This would cd into your project directory!

- List all entries: ```kwic ls```

- Remove an entry: ```kwic rm entryalias```

- Clear your clipboard history: ```kwic clear```

## Disclaimer

I've only been coding C for a couple of months now, and this is the first project I've built in it. Expect there to be bugs / errors I won't have picked up on.

Feel free to expand this and make any pull requests to help improve.

## Dependencies

Kwic only work on **Linux systems** with **Wayland**.
<br>
wl-clipboard is required, which can be installed via the terminal:

- Debian based: `sudo apt install wl-clipboard`

- Fedora / RHEL based: `sudo dnf install wl-clipboard`

- Arch based: `sudo pacman -S wl-clipboard`
<br><br><br><br>

<footer>Thanks for using Kwic :D</footer>