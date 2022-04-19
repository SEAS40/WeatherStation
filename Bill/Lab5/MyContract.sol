// SPDX-License-Identifier: GLP-3.0
pragma solidity >=0.5.0 <0.8.0;

contract Factory {

    uint idDigits = 16;
    uint idModulus = 10**idDigits;

struct Product{
        string name;
        uint id;

}

Product[] public products;

// Exercise 9
event NewProduct(uint ArrayProductId, string name, uint id);

function _createProduct(string memory _name, uint _id) private{
    products.push(Product(_name,_id));
    uint _ArrayProductId = products.length-1;

    emit NewProduct(_ArrayProductId,_name,_id);
 
}

function _generateRandomId(string memory _str) private view returns (uint) {
uint rand = uint(keccak256(abi.encodePacked(_str)));
return rand % idModulus;
}

// Exercise 8 part 2

function createRandomProduct(string memory _name) public {

uint randId = _generateRandomId(_name);
_createProduct(_name,randId);

}

// Exercise 10 Mapping

mapping(uint=>address) public productToOwner;
mapping(address=>uint) ownerProductCount;

// Exercise 11 Special Variables and Functions

function Ownership(uint _productId) public {

    productToOwner[msg.sender] = _productId;
    ownerProductCount[msg.sender]++;
    
}

// Exercise 12 Control Structures

function getProductsByOwner(address _owner) external view return(uint[] memory){
uint counter=0;
uint[] memory result = new uint[](ownerProductCount[_owner]);

for (uint i=0;x <= products.length,i++){
    if (productToOwner[i]==_owner){
        result[counter]=i;
        counter++;
    }

}

return result;
}


// Exercise 13 Inheritance

// New file .sol taking the in-built Ownable contract from OpenZeppelin


// Exercise 14 Error Handling and exceptions

mapping(uint=>uint) public age;

modifier olderThan(uint _age,uint _userID){ // modifier

    require(age[_userID] >= _age,"Authorized")
}

function validationUsers(uint _userID) public view olderthan(18,_userID){

}

// Exercise 15  Wrap-up

// sent by : bill.castillo@udc.es

}
