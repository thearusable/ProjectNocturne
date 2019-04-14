pipeline {

    environment {
        registry = "thearusable/nocturne"
        registryCredential = 'dockerhub'
    }

    // no default agent - need to be specified per stage
    agent none

    stages {
        stage('Docker'){
            agent any
            steps{
                script{
                    sh 'printenv'
                    // build docker image from dockerfile
                    sh 'docker build -t ${registry} .'
                    // publish image on docker hub
                    if (env.BRANCH_NAME == "develop"){
                        docker.withRegistry( '', registryCredential ) {
                            sh 'docker push ${registry}:latest'
                        }
                    } else {
                        sh 'echo "Not a develop branch - SKIPPING."'
                    }
                }
            }
        }
        stage ('Static analysis') {
            agent any
            steps {
                //cppcheck
		        sh 'cppcheck --enable=all --inconclusive --verbose --xml --xml-version=2 . 2> cppcheck_report.xml'
                publishCppcheck pattern:'cppcheck_report.xml'
            }
        }
        
        stage ('Build engine'){
            agent { docker { image 'thearusable/nocturne:latest' } }
            steps {
                dir('build')
                {
                    sh 'cmake ..'
                    sh 'make all'
                }
            }
        }

        stage ('Testing'){
            agent { docker { image 'thearusable/nocturne:latest' } }
            steps {
                dir('build')
                {
                    sh 'cmake ..'
                    sh 'make test'
                }
            } 
        }
    }
    post {
        always {
            emailext body: "${DEFAULT_CONTENT}",
                recipientProviders: [[$class: 'DevelopersRecipientProvider'], [$class: 'RequesterRecipientProvider']],
                subject: "${DEFAULT_SUBJECT}"
        }
    }
}
