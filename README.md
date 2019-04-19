# SimDim

> Whoop di scoop di poop

## What it do

A **really** simple display manager program. It just shows you what display managers you can run (set in the [config](#config) file), appends that to your `.xinitrc` and runs `startx`. That's it.

## Config
Format for the config file is as shown:
```
[name] : [/path/to/bin]
...
```

## License
[MIT][./LICENSE]
