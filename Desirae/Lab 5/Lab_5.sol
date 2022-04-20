// Lab 5: Desirae Minnett
// SPDX-License-Identifier: GLP-3.0

pragma solidity >=0.5.0 <0.8.0;

//E1
contract Factory {
    //E2
    uint idDigits = 16; 
    //E3
    uint idModulus = 10**idDigits; 

//E4
struct Product{ 
        string name;
        uint id;
}

//E5
Product[] public products;


event NewProduct(uint ArrayProductId, string name, uint id);

// E6
function _createProduct(string memory _name, uint _id) private{
    products.push(Product(_name,_id));
    uint _ArrayProductId = products.length-1;
    emit NewProduct(_ArrayProductId,_name,_id); //E9
}

//E7
function _generateRandomId(string memory _str) private view returns (uint) {

//E8
uint rand = uint(keccak256(abi.encodePacked(_str)));
return rand % idModulus;
}



function createRandomProduct(string memory _name) public {

uint randId = _generateRandomId(_name);
_createProduct(_name,randId);

}


mapping(uint=>address) public productToOwner;
mapping(address=>uint) ownerProductCount;

//E10 & E11
function Ownership(uint _productId) public {
    productToOwner[_productId] = msg.sender ;
    ownerProductCount[msg.sender]++;
}

//E12
function getProductsByOwner (address _owner) external view returns(uint[] memory) {
    
uint counter=0;
uint[] memory result = new uint[](ownerProductCount[_owner]);

for (uint i=0;i <= products.length;i++){
    if (productToOwner[i]==_owner){
        result[counter]=i;
        counter++;
    }

}

return result;
}

//E14
mapping(uint=>uint) public age;

modifier olderThan(uint _age,uint _userID) { // modifier
    require(age[_userID] >= _age,"Authorized");
    _;
}

function validationUsers(uint _userID) public view olderThan(18,_userID){

}

}
