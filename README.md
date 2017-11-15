# terse
An evaluator for a python-like language implemented as a project in INF225 (University of Bergen).

Example code that can be interpreted by the evaluator:

    print("Hello world!\n")
    
    //Named scope
    sc stuff
    	let pi = 3.141592
    	let xs = [14, 2, 25, 5]
    	
    	//Fibonacci function
    	fn fib(n)
    		let a = 0, b = 1, i = 1
    		while i++ < n
    			let ith = a + b
    			a := b
    			b := ith
    		return b
    
    	//Map function
    	fn map(f, xs)
    		let ys = []
    		for x in xs
    			append(ys, f(x))
    		return ys
    
    print("Map fib to xs: ", stuff.map(stuff.fib, stuff.xs), '\n')
    
    /*
    Can use block comments as well.
    Demonstrate how functions are closures:
    */
    fn foo()
    	let x = 0
    	fn get()
    		return x
    	fn inc()
    		x++
    	return [get, inc]
    
    let a = foo(), b = foo()
    a[1]()
    a[1]()
    print("a = ", a[0](), ", b = ", b[0](), '\n')
    
    /*
    Can create objects by returning scopes.
    */
    fn pair(x, y)
      sc this
        let first = x, second = y
      return this
    
    let c = pair(42, 3.141592)
    print("c = (", c.first, ", ", c.second, ")\n")
