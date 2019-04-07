pipeline {

    environment {
        registry = "thearusable/nocturne"
        registryCredential = 'dockerhub'
        image = ''
    }

    //agent {
    //    docker { image 'thearusable/nocturne:latest' }
    //}

    agent none

    //agent {
    //    dockerfile {
    //        filename 'Dockerfile'
    //        additionalBuildArgs '-t thearusable/nocturne'
    //    }
    //}

    stages {

        stage('Build image'){
            agent any
            steps{
                script{
                    sh 'docker build -t thearusable/nocturne .'
                }
            }
        }

        //stage('Publish image'){
        //    agent any
        //    steps{
        //        script{
        //            sh 'docker push thearusable/nocturne:latest'
        //        }
        //    }
        //}

        stage('Docker Push') {
            agent any
            steps {
                script{
                    docker.withRegistry( '', registryCredential ) {
                        sh 'docker push thearusable/nocturne:latest'
                    }
                }
                withCredentials([usernamePassword(credentialsId: 'dockerhub', passwordVariable: 'dockerHubPassword', usernameVariable: 'dockerHubUser')]) {
                    sh "docker login -u ${env.dockerHubUser} -p ${env.dockerHubPassword}"
                    sh 'docker push thearusable/nocturne:latest'
                }
            }
    }

        //stage ('Build image') {
        //    steps{
        //        script {
                    // build image
        //            image = docker.build registry

                    // only push docker image when build from develop branch
        //            if (env.BRANCH_NAME == "develop"){
        //                docker.withRegistry('', registryCredential) {
        //                    image.push("latest")
        //                }
        //            } else {
        //                sh 'echo "Not a develop branch - SKIPPING."'
        //            }
        //        }
        //    }
        //}

        //stage ('Pre-analysis') {
        //    steps {
		//        sh 'cppcheck --enable=all --inconclusive --verbose --xml --xml-version=2 . 2> cppcheck_report.xml'
        //    }
        //}
        
        stage ('Build engine'){
            steps {
                dir('build')
                {
                    sh 'cmake ..'
                    sh 'make'
                }
            }
        }
    }
    //post {
	//    always {
	//        publishCppcheck pattern:'cppcheck_report.xml'
	//    }           
    //}
}
