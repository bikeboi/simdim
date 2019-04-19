# SimDim

> Whoop di scoop di poop

## What it do

A **really** simple display manager program. It just shows you what desktop/window managers you can run (set in the [config](#config) file), appends that to your `.xinitrc` and runs `startx`. That's it.

## Config
Format for the config file is as shown:
```
...
window-manager-name : /path/to/its/bin
...
```
The program looks for this file in the usual `~/.config/dmanrc`

## License
[MIT](./LICENSE)
