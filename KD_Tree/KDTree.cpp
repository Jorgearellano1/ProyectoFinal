#include "KDTree.h"
#include <algorithm>
#include <iostream>

KDTree::KDNode::KDNode(const std::vector<float> &pt) : point(pt), left(nullptr), right(nullptr) {}

KDTree::KDTree() : root(nullptr) {}

KDTree::~KDTree() {
    clear(root);
}

void KDTree::clear(KDNode* node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

bool KDTree::arePointsEqual(const std::vector<float> &point1, const std::vector<float> &point2) {
    for (size_t i = 0; i < point1.size(); ++i) {
        if (point1[i] != point2[i])
            return false;
    }
    return true;
}

KDTree::KDNode* KDTree::insertRec(KDNode* node, const std::vector<float> &point, unsigned depth) {
    if (node == nullptr) {
        std::cout << "Insertando punto: (";
        for (float p : point) std::cout << p << " ";
        std::cout << ") a la profundidad " << depth << std::endl;
        return new KDNode(point);
    }

    unsigned cd = depth % point.size();
    if (point[cd] < node->point[cd]) {
        std::cout << "Yendo a la izquierda a la profundidad " << depth << " para el punto: (";
        for (float p : point) std::cout << p << " ";
        std::cout << ")" << std::endl;
        node->left = insertRec(node->left, point, depth + 1);
    } else {
        std::cout << "Yendo a la derecha a la profundidad " << depth << " para el punto: (";
        for (float p : point) std::cout << p << " ";
        std::cout << ")" << std::endl;
        node->right = insertRec(node->right, point, depth + 1);
    }
    return node;
}

void KDTree::insert(const std::vector<float> &point) {
    root = insertRec(root, point, 0);
}

bool KDTree::searchRec(KDNode* node, const std::vector<float> &point, unsigned depth) {
    if (node == nullptr) {
        std::cout << "Punto no encontrado: (";
        for (float p : point) std::cout << p << " ";
        std::cout << ")" << std::endl;
        return false;
    }
    if (arePointsEqual(node->point, point)) {
        std::cout << "Punto encontrado: (";
        for (float p : point) std::cout << p << " ";
        std::cout << ")" << std::endl;
        return true;
    }

    unsigned cd = depth % point.size();
    if (point[cd] < node->point[cd]) {
        std::cout << "Buscando a la izquierda a la profundidad " << depth << " para el punto: (";
        for (float p : point) std::cout << p << " ";
        std::cout << ")" << std::endl;
        return searchRec(node->left, point, depth + 1);
    }
    std::cout << "Buscando a la derecha a la profundidad " << depth << " para el punto: (";
    for (float p : point) std::cout << p << " ";
    std::cout << ")" << std::endl;
    return searchRec(node->right, point, depth + 1);
}

bool KDTree::search(const std::vector<float> &point) {
    return searchRec(root, point, 0);
}

KDTree::KDNode* KDTree::findMinRec(KDNode* node, unsigned dim, unsigned depth) {
    if (node == nullptr) {
        return nullptr;
    }

    unsigned cd = depth % dim;
    if (cd == dim) {
        if (node->left == nullptr) {
            return node;
        }
        return findMinRec(node->left, dim, depth + 1);
    }

    KDNode* left = findMinRec(node->left, dim, depth + 1);
    KDNode* right = findMinRec(node->right, dim, depth + 1);
    KDNode* minNode = node;

    if (left != nullptr && left->point[dim] < minNode->point[dim]) {
        minNode = left;
    }
    if (right != nullptr && right->point[dim] < minNode->point[dim]) {
        minNode = right;
    }
    return minNode;
}

KDTree::KDNode* KDTree::deleteRec(KDNode* node, const std::vector<float> &point, unsigned depth) {
    if (node == nullptr) {
        return nullptr;
    }

    unsigned cd = depth % point.size();
    if (arePointsEqual(node->point, point)) {
        std::cout << "Eliminando punto: (";
        for (float p : point) std::cout << p << " ";
        std::cout << ")" << std::endl;
        if (node->right != nullptr) {
            KDNode* minNode = findMinRec(node->right, cd, depth + 1);
            node->point = minNode->point;
            node->right = deleteRec(node->right, minNode->point, depth + 1);
        } else if (node->left != nullptr) {
            KDNode* minNode = findMinRec(node->left, cd, depth + 1);
            node->point = minNode->point;
            node->right = deleteRec(node->left, minNode->point, depth + 1);
            node->left = nullptr;
        } else {
            delete node;
            return nullptr;
        }
    } else if (point[cd] < node->point[cd]) {
        std::cout << "Yendo a la izquierda a la profundidad " << depth << " para eliminar el punto: (";
        for (float p : point) std::cout << p << " ";
        std::cout << ")" << std::endl;
        node->left = deleteRec(node->left, point, depth + 1);
    } else {
        std::cout << "Yendo a la derecha a la profundidad " << depth << " para eliminar el punto: (";
        for (float p : point) std::cout << p << " ";
        std::cout << ")" << std::endl;
        node->right = deleteRec(node->right, point, depth + 1);
    }
    return node;
}

void KDTree::deletePoint(const std::vector<float> &point) {
    root = deleteRec(root, point, 0);
}
