![alt text](../img/banner.jpg "banner")
# Appendix B: FM Profiles <a id="fmprofiles"></a>

This section specifies the attributes and rules for the following list of profiles.

| Profile description                                                | profile_id| calcrule_id |
|:-------------------------------------------------------------------|-----------|------------:|
| Deductible and limit                                               | 1         |   1         |
| Franchise deductible and limit                                     | 2         |   3         |
| Deductible only                                                    | 3         |  12         |
| Maximum Deductible                                                 | 4         |  10         |
| Minimum Deductible                                                 | 5         |  11         |
| Deductible, limit and share                                        | 6         |   2         |
| Deductible and limit as a proportion of loss                       | 10        |   5         |
| Limit with deductible as a proportion of limit                     | 11        |   9         |
| Limit only                                                         | 12        |   14        |
| Limit as a proportion of loss                                      | 13        |   15        |
| Deductible as a proportion of loss                                 | 14        |   16        |

An allocation rule can be assigned to any profile at any stage in the calculation, which determines whether calculated losses should be back-allocated to the contributing items, and if so how. This is specified via an allocrule_id in the fm_profile data. 

The choices are as follows;

| Allocrule description                                              | allocrule_id|
|:-------------------------------------------------------------------|------------:|
| Don't back-allocate losses                                         | 0           |
| Back allocate losses to items in proportion to ground up loss      | 1           |
| Back-allocate losses to items in proportion to previous level loss | 2           |

In the following notation;
* x.loss is the input loss to the calculation
* x.retained_loss is the input retained loss to the calculation (where required)
* loss is the calculated loss 
* ded, lim, and share are alias variables for the profile fields as required

### 1. Deductible and limit

| Attributes                        | Example |
|:----------------------------------|--------:|
| policytc_id                       | 1       |
| ccy_id                            | 1       |
| deductible                        | 50000   |
| limit                             | 900000  |

| Rules                             | Value   |
|:----------------------------------|--------:|
| calcrule_id                       | 1       | 

##### Calculation logic
``` sh
loss = x.loss - ded;
if (loss < 0) loss = 0;
if (loss > lim) loss = lim;
```
### 2. Franchise deductible and limit

| Attributes                        | Example |
|:----------------------------------|--------:|
| policytc_id                       | 1       |
| ccy_id                            | 1       |
| deductible                        | 100000  |
| limit                             | 1000000 |

| Rules                             | Value   |
|:----------------------------------|--------:|
| calcrule_id                       | 3       | 

##### Calculation logic

``` sh
if (x.loss < ded) loss = 0;
	else loss = x.loss;
if (loss > lim) loss = lim;
```

### 3. Deductible only

| Attributes                        | Example |
|:----------------------------------|--------:|
| policytc_id                       | 1       |
| ccy_id                            | 1       |
| deductible                        | 100000  |

| Rules                             | Value   |
|:----------------------------------|--------:|
| calcrule_id                       | 12      | 

##### Calculation logic

``` sh
loss = x.loss - ded;
if (loss < 0) loss = 0;
```

### 4. Maximum deductible

If the accumulated deductibles from the previous level exceed the maximum deductible, the deductible is capped at the maximum deductible value

| Attributes                        | Example |
|:----------------------------------|--------:|
| policytc_id                       | 1       |
| ccy_id                            | 1       |
| deductible                        | 40000   |

| Rules                             | Value   |
|:----------------------------------|--------:|
| calcrule_id                       | 10      | 

##### Calculation logic

``` sh
if (x.retained_loss > ded) { 
	loss = x.loss + x.retained_loss - ded;
	if (loss < 0) loss = 0;
	}
else {
	loss = x.loss;
     }
```

### 5. Minimum deductible

If the accumulated deductibles from the previous level are less than the minimum deductible, the deductible is increased to the total loss or the minimum deductible value, whichever is greater.

| Attributes                        | Example |
|:----------------------------------|--------:|
| policytc_id                       | 1       |
| ccy_id                            | 1       |
| deductible                        | 70000   |

| Rules                             | Value   |
|:----------------------------------|--------:|
| calcrule_id                       | 11      | 

##### Calculation logic

``` sh
if (x.retained_loss < ded) { 
	loss = x.loss + x.retained_loss - ded;
	if (loss < 0) loss = 0;
	}
else {
	loss = x.loss;
     }
```

### 6. Deductible, limit and share

| Attributes                        | Example |
|:----------------------------------|--------:|
| policytc_id                       | 1       |
| ccy_id                            | 1       |
| deductible                        | 70000   |
| limit                             | 1000000 |
| share_prop_of_lim                 | 0.1     |

| Rules                             | Value   |
|:----------------------------------|--------:|
| calcrule_id                       | 2       | 

##### Calculation logic

``` sh
if (x.loss > (ded + lim)) loss = lim;
	else loss = x.loss - ded;
if (loss < 0) loss = 0;
loss = loss * share;
```

### 10. Deductible and limit as a proportion of loss

| Attributes                        | Example |
|:----------------------------------|--------:|
| policytc_id                       | 1       |
| deductible_prop_of_loss           | 0.05    |
| limit_prop_of_loss                | 0.3     |

| Rules                             | Value   |
|:----------------------------------|--------:|
| calcrule_id                       | 5       | 

##### Calculation logic

``` sh
loss = x.loss * (lim - ded);
```

### 11. Limit with deductible as a proportion of limit

| Attributes                        | Example |
|:----------------------------------|--------:|
| policytc_id                       | 1       |
| ccy_id                            | 1       |
| deductible_prop_of_loss           | 0.05    |
| limit                             | 100000  |

| Rules                             | Value   |
|:----------------------------------|--------:|
| calcrule_id                       | 9       | 

##### Calculation logic

``` sh
loss = x.loss - (ded * lim);
if (loss < 0) loss = 0;
if (loss > lim) loss = lim;
```

### 12. Limit only

| Attributes                        | Example |
|:----------------------------------|--------:|
| policytc_id                       | 1       |
| ccy_id                            | 1       |
| limit                             | 100000  |

| Rules                             | Value   |
|:----------------------------------|---------|
| calcrule_id                       | 14      | 

##### Calculation logic

``` sh
loss = x.loss;
if (loss > lim) loss = lim;
```

### 13. Limit as a proportion of loss

| Attributes                        | Example |
|:----------------------------------|--------:|
| policytc_id                       | 1       |
| limit_prop_of_loss                | 0.3     |

| Rules                             | Value   |
|:----------------------------------|--------:|
| calcrule_id                       | 15      | 

##### Calculation logic

``` sh
loss = x.loss;
loss = loss * lim;
```

### 14. Deductible as a proportion of loss

| Attributes                        | Example |
|:----------------------------------|--------:|
| policytc_id                       | 1       |
| deductible_prop_of_loss           | 0.05    |

| Rules                             | Value   |
|:----------------------------------|--------:|
| calcrule_id                       | 16      | 

##### Calculation logic

``` sh
loss = x.loss;
loss = loss - (loss * ded);
if (loss < 0) loss = 0;
```
[Return to top](#fmprofiles)

[Go to Appendix C Multi-peril model support](MultiPeril.md)

[Back to Contents](Contents.md)
