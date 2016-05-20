# How to use the websocket
Using the websocket involves sending JSON formatted objects. The structure of 
these objects is relatively straightforward, two keys are required: 
`animation_class` and `animation_parameters`.

`animation_class` references a Python object that implements the `Animation` 
specification. The easiest example is a `KeyframeAnimation`.

`animation_module` (possibly) references the module of which the class 
shall be  imported

`animation_parameters` is a dict of named parameters for the python class, it 
is advisable that the python code defaults parameters. The dict will be 
passed to the python class as `**kwargs`

# Keyframe example
```
{
    "animation_class":  "KeyframeAnimation",
    "animation_parameters": {
        "frames":
            [[
                { "r": 255, "g": 0, "b": 0 },
                ...
                { "r": 255, "g": 0, "b": 0 },
            ],
            ...
                { "r": 255, "g": 0, "b": 0 },
                ...
                { "r": 255, "g": 0, "b": 0 },
            ]]
   }
}
```
