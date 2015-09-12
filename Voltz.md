# Voltz IO API

## Iteratable[T]
- `Iterator():std::Iterator[T]`

## Iterator[T]
- `HasNext():std::Bool`
- `Next():T`
- `Remove()`

## Collection[T] : Iteratable
- `Empty():std::Bool`
- `Count():std::Int`
- `Contains(:T)`
- `Add(:T):std::Collection[T]` - Returns a collection because collections are immutable.
- `Add(Collection:std::Collection[T]):std::Collection[T]`
- `ToArray():std::Array[T]`

## Generic
- `GetGenericTypes():std::Array[std::Class]`

## WriteStream
- `Write(Data:std::Array[std::Byte]):std::Int`
- `Flush()`
- `Close()`

## ReadStream
- `Read(Count:std::Int):std::Array[std::Byte]`
- `Close()`

## CharacterEncoder
- `Encode(Character:std::Character):std::Array[std::Byte]`

## CharacterDecoder
- `Decode(Get:():std::Byte):(std::Character,std::Int)`

## CharacterWriteStream
- `Init()`
- `Init(Encoder:std::io::CharacterEncoder)`
- `Write(Character:std::Character):std::Int`
- `Write(Character:std::Character,Encoder:std::io::CharacterEncoder):std::Int`
- `Write(String:std::String):std::Array[std::Int]`
- `Write(String:std::String,Encoder:std::io::CharacterEncoder):std::Array[std::Int]`

## CharacterReadStream
- `Init()`
- `Init(Decoder:std::io::CharacterDecoder)`
- `Read():(std::Character,std::Int)`
- `Read(Decoder:std::io::CharacterDecoder):(std::Character,std::Int)`
- `Read(Count:std::Int):(std::String,std::Array[std::Int])`
- `Read(Count:std::Int,Decoder:std::io::CharacterDecoder):(std::String,std::Array[std::Int])`

## MultiWriteStream ?
