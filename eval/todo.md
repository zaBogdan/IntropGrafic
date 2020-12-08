# Usage

### readFunction
TBD
### parseByOperators
* **Input**: `string Function` 
* **Output**: `Tree expression`

### checkFunctionValidity
* **Input**: `Tree expression`
* **Output**: `boolean`

### Definition Intervals
* **Input**: `Tree expression`
* **Output**: `vector<Intervals>`

### constructValidFunction
* **Input**: `Tree expression, vector<Intervals> definedpoints, boolean validity`
* **Output**:
```
-> If function is valid: 
struct operationalFunction{
    string validFunction;
    vector<Intervals> definedPoints;
}
-> If function is invalid:
NULL
```

### stringToCPPFunction
* **Input**: `operationalFunction func`
* **Output**: `boolean`
* **Note:**: This function will save a binary file in the eval directory called func.cpp and it will be added on the main project. 