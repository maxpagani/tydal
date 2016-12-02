# Tydal Specifications

# Introduction
Applications store and communication structured information by using types. In order to specify types formal languages are often used. The advantage is that the documentation is less prone to misinterpretation and it can be used for automatic processing to create source code, test cases and configuration files.
This document specify Tydal (TYpe Definition Astounding Language) a type definition language specifically targeted at defining types that can be later encoded in [JSON](http://json.org/).

## Dictionary
A list of specific terms and acronyms used throughout in this document.
**API**: Application Programmer Interface
**JMS**: Java Message Service: Java Enterprise messaging that allows Java and Scala programs to exchange data either on the same JVM or among remote JVMs.
**JVM**: Java Virtual Machine: the virtual environment where Java and Scala programs run.
Namespace: A set of symbols used to organize web-service names. In this document namespaces define the path to identify a specific web-service.
**TBD**: To Be Defined. Used in this text to mark uncomplete or temporary information.

## Notes to the release

# Tydal Informal Description
This section describes the language in an informal manner. This is useful to get a grasp of the langauge.
## Values
Values (constant literals) are written using the [JSON](http://json.org/) convention1. According to this convention the type used for a given value is implicit in the notation used:
> “text” → String
> 23 → Integer number (decimal)
> 3.14 → floating point number
> true → boolean value true
> false → boolean value false.
> { “field_1”: value_1, “field_2”: value_2 } → record with fields named field_1 and field_2.
> [ value_1, value_2, ... ] → an array composed of items value_1, value_2, ...
By combining these elements you may build complex values.

## Types
Aggregate types are defined in terms of structures where fields have a name and a type. The following notation is used to define a field:
    name : type
Where type is one of the following:
> **`String`** → to define a text string
> **`Int`** → to define an integer number
> **`Boolean`** → a boolean value (either true or false)
> **`Float`** → to define a floating point number
> **`Array[T]`** → to define an array of type T
> **`Record`** … **`End`** → to define a record containing one or more comma-separated fields.
> **`Enum`** … **`End`** → to define an enumeration with one or more comma-separated symbolic values.
> *TypeAlias* → a name you can give to a complex type for reuse or improve readability.
Commas, in comma separated structure, may be omitted for the purpose of this document if the layout provides enough information to distinguish different elements.
Within a record an optional field is preceded by the keyword **`opt`**.
Also within a record you can define an optional group of fields. Either all the fields in the group are in the record or they are not. The syntax is defined as follows:
    Record
    …
        opt Group
            fieldA: Type
            fieldB: Type
            …
        End
    …
    End
Comments can be written inline and are introduced by the '`#`' character.
### Variant
Within a record a variant record may be defined by marking a field with **`Variant keyword`**. Different versions of the record are marked with the keyword **`Case`** followed by that variant definition.
E.g.
    Record
        centerX: Int
        centerY: Int
        Variant type: String
            Case “SQUARE” 
                side: Int
            Case “RECTANGLE”
                length: Int
                height: Int
            Case “CIRCLE”
                radius: Int
        End
    End
This allows the language to express three different types that share a common part. Which part is actually used is defined by the value of the field named after **`Variant`** statement.
Field type is named discriminator of the variant. Each branch has a value literal that must be a valid literal of the type of the discriminator.
The variant part may be also selected on a field of an enclosing record. To accomplish this feature the syntax is the following:
    Record
        …
        d: BasicType 
        r : Record
            Variant d: ^
                Case bt0
                    …
                Case bt1
                   …
            End
        End
    End
Note that the name of the field in the outer record and the name of the field of the variant structure are the same. The symbol ‘^’ has been chosen as an arrow pointing to where the definition of the field is. Constant types in the variant branches must match the type of the variant field discriminator.
### Type naming
A Type can be named by using the **`Type`** construct:
    Type T : Record
        …
    End
From this point onward the name T can be used where a type is expected.
### Partial Records
Sometimes there are complex types that are conveniently defined in multiple units. Consider a message type which has a common headers and many variants. Defining this type in a single place can be daunting for the writer and confusing for the reader. By using *partial records* you can split the record definition in multiple units.
    Type A: Partial Record
        … 
    End
Type A is defined by the union of all the partial records found in the definition. Fields in the single definitions of the partial records must be unique, with the only exception of the variants. If a variant has the same name, it must have the same type and all the different variants are included in the definition.
## String formats
String is the underlying type for a number of string type. More precisely Date, Time, Timestamp (DateTime), Enumeration and identifiers. In these case the type String is decorated with the specific type in parenthesis:
> `String(Date)` → a string containing a date.
> `String Type Id` → declare Id to be a specific string type – not compatible with other string types.
> `String(Id)` → a string containing an identifier of type “Id”
    Type State: Enum
        IDLE,
        LEFT_TO_RIGHT,
        RIGHT_TO_LEFT
    End
> `String(State)` → a string containing a State enumeration value.
String Type construct is a kind of type definition used to declare string specialization. There is no mechanism to define the inner structure or the interface of these types, since this Is defined to be out of scope2.
The notation is somewhat redundant, since String(T) could have been replaced by T, but this is intended to remark that this typing is just a weak convention over the implementation type.
***Dates*** are expressed using the [ISO standard 86013](https://en.wikipedia.org/wiki/ISO_8601). The pattern used is YYYY-MM-DD with or without the dashes (YYYYMMDD) where YYYY is the year, MM is the month (1 is January, 2 is February, …) and DD is the day (1 is the first day of the month). Both month (MM) and day (DD) are left padded with '0' (zero) to be written always with two characters. Example: “2015-10-08” is October, 8th 2015.
***Time*** (expressing either a duration or the time of the day) is expressed by using the 24 hours notation, although values greater than 24 can be used when expressing duration. The time duration is expressed as hours, minutes and seconds, optionally the milliseconds are added as decimal part of the seconds, according to the following template: H:MM:SS where H represent hours, MM is the 2 digits minutes (in the range 0-59), SS represents the seconds and is expressed as a decimal value or optionally as a fixed point value. The integer part of the seconds is left-padded with '0' (zero) to reach two character length. The part on the right of the decimal point can be from one to three digits without padding.

> Examples:
> **Valid**
> 11:04:23
> 9:23:01.12
> **Not Valid**
> 11:4:23	(no padding 0 for minutes)
> 9:23:01.	(decimal point, but no milliseconds)

***Timestamps*** are composed by a date followed by an UTC time and the optional timezone. Timestamp is formatted according to the [ISO standard 86014](https://en.wikipedia.org/wiki/ISO_8601). Time representation may specify the timezone. Example: “2015-10-08T09:35:21+01:00” specify October, 8th 2015, 9:35am, CET (GMT+1) timezone. If no timezone is specified, server local timezone is assumed. Milliseconds may be indicated as a decimal part of seconds.
